// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

/**
 * Unicode character database ``<ogonek/ucd.h++>``
 * ===============================================
 */

#ifndef OGONEK_UCD_HPP
#define OGONEK_UCD_HPP

#include <ogonek/ucd/ucd_all.g.h++>
#include <ogonek/types.h++>
#include <ogonek/detail/static_const.h++>

#include <boost/logic/tribool.hpp>
#include <boost/optional.hpp>
#include <boost/rational.hpp>

#include <algorithm>
#include <iterator>
#include <string>
#include <utility>

#include <cstddef>
#include <cstring>

namespace ogonek {
    /**
     * .. note:: The items in this section are in the namespace ``ogonek::ucd``.
     */
    namespace ucd {
        /**
        * .. var:: constexpr auto maybe = boost::indeterminate
        *
        *     An alternative name for ``boost::indeterminate``.
        */
        BOOST_TRIBOOL_THIRD_STATE(maybe)

        namespace detail {
            inline boost::tribool to_tribool(ogonek::detail::trinary t) {
                switch(t.value) {
                    case -1:
                        return maybe;
                    default:
                        return t.value;
                }
            }
            inline boost::optional<boost::rational<long>> to_rational(ogonek::detail::fraction f) {
                if(f.den == 0) return boost::none;
                else return boost::rational<long>(f.num, f.den);
            }

            template <typename It>
            std::reverse_iterator<It> make_reverse(It it) {
                return std::reverse_iterator<It>(it);
            }
            struct property_group_comparer {
                template <typename T>
                bool operator()(code_point u, T const& g) const {
                    return u >= g.start;
                }
            };
            template <typename T>
            T const& find_property_group(T const* first, std::size_t size, code_point u) {
                return *std::upper_bound(make_reverse(first + size), make_reverse(first), u, property_group_comparer{});
            }

            inline void add_hex(code_point u, std::string& s) {
                char const hex[] = "0123456789ABCDEF";
                int factor;
                if(u > 0xFFFFF) factor = 0x100000;
                else if(u > 0xFFFF) factor = 0x10000;
                else factor = 0x1000;
                for(; factor > 0; u %= factor, factor /= 0x10) {
                    s.push_back(hex[u / factor]);
                }
            }
            template <std::size_t N>
            std::string make_ideograph_name(code_point u, char const (&base)[N]) {
                std::string result;
                result.reserve(N + 5);
                result = base;
                add_hex(u, result);
                return result;
            }
            inline char const* get_jamo_short_name(code_point u) {
                return detail::find_property_group(jamo_short_name_data, jamo_short_name_data_size, u).value;
            }
            template <std::size_t N>
            std::string make_hangul_syllable_name(code_point u, char const (&base)[N]) {
                const int sbase = 0xAC00;
                const int lbase = 0x1100;
                const int vbase = 0x1161;
                const int tbase = 0x11A7;
                const int tcount = 28;
                const int ncount = 588;

                auto sindex = u - sbase;
                auto lindex = sindex / ncount;
                auto vindex = (sindex % ncount) / tcount;
                auto tindex = sindex % tcount;
                auto lpart = lbase + lindex;
                auto vpart = vbase + vindex;
                auto tpart = tbase + tindex;

                std::string result;
                result.reserve(N + 9);
                result += base;
                result += detail::get_jamo_short_name(lpart);
                result += detail::get_jamo_short_name(vpart);
                if(tindex > 0) result += detail::get_jamo_short_name(tpart);
                return result;
            }
        } // namespace detail

#define OGONEK_UCD_QUERY(type, name, query) \
        namespace fun {\
            struct query {\
                type operator()(code_point u) const {\
                    return detail::find_property_group(name##_data, name##_data_size, u).value;\
                }\
            };\
        } /* namespace fun */ \
        inline namespace {\
            constexpr auto const& query = ogonek::detail::static_const<fun::query>::value;\
        }\
        static_assert(true, "")
#define OGONEK_UCD_GETTER(type, name) OGONEK_UCD_QUERY(type, name, get_##name)
#define OGONEK_UCD_TESTER(name) OGONEK_UCD_QUERY(bool, name, is_##name)
#define OGONEK_UCD_TESTER3(name) \
        namespace fun {\
            struct get_##name {\
                boost::tribool operator()(code_point u) const {\
                    auto value = detail::find_property_group(name##_data, name##_data_size, u).value;\
                    return detail::to_tribool(value);\
                }\
            };\
        } /* namespace fun */ \
        inline namespace {\
            constexpr auto const& get_##name = ogonek::detail::static_const<fun::get_##name>::value;\
        }\
        static_assert(true, "")
#define OGONEK_UCD_CODE_POINT_GETTER(name) \
        namespace fun {\
            struct get_##name {\
                code_point operator()(code_point u) const {\
                    auto value = detail::find_property_group(name##_data, name##_data_size, u).value;\
                    if(value == code_point(-1)) return u;\
                    else return value;\
                }\
            };\
        } /* namespace fun */ \
        inline namespace {\
            constexpr auto const& get_##name = ogonek::detail::static_const<fun::get_##name>::value;\
        }\
        static_assert(true, "")

        /**
         * .. function:: version get_age(code_point u)
         *
         *     :returns: the *Age* property of ``u``
         */
        OGONEK_UCD_GETTER(version, age);

        /**
         * .. function:: std::string get_name(code_point u)
         *
         *     :returns: the *Name* property of ``u``
         */
        namespace fun {
            struct get_name {
                std::string operator()(code_point u) const {
                    auto value = detail::find_property_group(name_data, name_data_size, u).value;
                    if(value[0] != '<') return value;

                    if(std::strcmp(value, "<CJK Ideograph>") == 0
                    || std::strcmp(value, "<CJK Ideograph Extension A>") == 0
                    || std::strcmp(value, "<CJK Ideograph Extension B>") == 0
                    || std::strcmp(value, "<CJK Ideograph Extension C>") == 0
                    || std::strcmp(value, "<CJK Ideograph Extension D>") == 0
                    || std::strcmp(value, "<CJK Ideograph Extension E>") == 0) {
                        return detail::make_ideograph_name(u, "CJK UNIFIED IDEOGRAPH-");
                    }
                    if(std::strcmp(value, "<Hangul Syllable>") == 0) {
                        return detail::make_hangul_syllable_name(u, "HANGUL SYLLABLE ");
                    }
                    return {};
                }
            };
        } //namespace fun
        inline namespace {
            constexpr auto const& get_name = ogonek::detail::static_const<fun::get_name>::value;
        }

        /**
         * .. function:: block get_block(code_point u)
         *
         *     :returns: the *Block* property of ``u``
         */
        OGONEK_UCD_GETTER(block, block);
        /**
         * .. function:: block get_general_category(code_point u)
         *
         *     :returns: the *General_Category* property of ``u``
         */
        OGONEK_UCD_GETTER(general_category, general_category);
        /**
         * .. function:: combining_class get_canonical_combining_class(code_point u)
         *
         *     :returns: the *Canonical_Combining_Class* property of ``u``
         */
        OGONEK_UCD_GETTER(combining_class, canonical_combining_class);
        /**
         * .. function:: bidi_class get_bidi_class(code_point u)
         *
         *     :returns: the *Bidi_Class* property of ``u``
         */
        OGONEK_UCD_GETTER(bidi_class, bidi_class);
        /**
         * .. function:: bool is_bidi_mirrored(code_point u)
         *
         *     :returns: true if ``u`` has the *Bidi_Mirrored* property; false otherwise
         */
        OGONEK_UCD_TESTER(bidi_mirrored);
        /**
         * .. function:: code_point get_bidi_mirroring_glyph(code_point u)
         *
         *     :returns: the *Bidi_Mirroring_Glyph* property of ``u``
         */
        OGONEK_UCD_CODE_POINT_GETTER(bidi_mirroring_glyph);
        /**
         * .. function:: bool is_bidi_control(code_point u)
         *
         *     :returns: true if ``u`` has the *Bidi_Control* property; false otherwise
         */
        OGONEK_UCD_TESTER(bidi_control);
        /**
         * .. function:: code_point get_bidi_paired_bracket(code_point u)
         *
         *     :returns: the *Bidi_Paired_Bracket* property of ``u``
         */
        OGONEK_UCD_CODE_POINT_GETTER(bidi_paired_bracket);
        /**
         * .. function:: bracket_type get_bidi_paired_bracket_type(code_point u)
         *
         *     :returns: the *Bidi_Paired_Bracket_Type* property of ``u``
         */
        OGONEK_UCD_GETTER(bracket_type, bidi_paired_bracket_type);
        /**
         * .. function:: decomposition_type get_decomposition_type(code_point u)
         *
         *     :returns: the *Decomposition_Type* property of ``u``
         */
        OGONEK_UCD_GETTER(decomposition_type, decomposition_type);

        /**
         * .. function:: std::u32string get_decomposition_mapping(code_point u)
         *
         *     :returns: the *Decomposition_Mapping* property of ``u``
         */
        namespace fun {
            struct get_decomposition_mapping {
                std::u32string operator()(code_point u) const {
                    auto value = detail::find_property_group(decomposition_mapping_data, decomposition_mapping_data_size, u).value;
                    if(value) return value;
                    else return std::u32string(1, u);
                }
            };
        } // namespace fun
        inline namespace {
            constexpr auto const& get_decomposition_mapping = ogonek::detail::static_const<fun::get_decomposition_mapping>::value;
        }

        /**
         * .. function:: bool is_excluded_from_composition(code_point u)
         *
         *     :returns: true if ``u`` has the *Full_Composition_Exclusion* property; false otherwise
         */
        OGONEK_UCD_QUERY(bool, full_composition_exclusion, is_excluded_from_composition);
        /**
         * .. function:: boost::tribool get_nfc_quick_check(code_point u)
         *
         *     :returns: the *NFC_Quick_Check* property of ``u``
         */
        OGONEK_UCD_TESTER3(nfc_quick_check);
        /**
         * .. function:: bool get_nfd_quick_check(code_point u)
         *
         *     :returns: the *NFD_Quick_Check* property of ``u``
         */
        OGONEK_UCD_GETTER(bool, nfd_quick_check);
        /**
         * .. function:: boost::tribool get_nfkc_quick_check(code_point u)
         *
         *     :returns: the *NFKC_Quick_Check* property of ``u``
         */
        OGONEK_UCD_TESTER3(nfkc_quick_check);
        /**
         * .. function:: bool get_nfkd_quick_check(code_point u)
         *
         *     :returns: the *NFKD_Quick_Check* property of ``u``
         */
        OGONEK_UCD_GETTER(bool, nfkd_quick_check);
        /**
         * .. function:: numeric_type get_numeric_type(code_point u)
         *
         *     :returns: the *Numeric_Type* property of ``u``
         */
        OGONEK_UCD_GETTER(numeric_type, numeric_type);

        /**
         * .. function:: boost::optional get_numeric_value(code_point u)
         *
         *     :returns: the *Numeric_Value* property of ``u``, if present; none otherwise
         */
        namespace fun {
            struct get_numeric_value {
                boost::optional<boost::rational<long>> operator()(code_point u) const {
                    auto value = detail::find_property_group(numeric_value_data, numeric_value_data_size, u).value;
                    return detail::to_rational(value);
                }
            };
        } // namespace fun
        inline namespace {
            constexpr auto const& get_numeric_value = ogonek::detail::static_const<fun::get_numeric_value>::value;
        }

        /**
         * .. function:: joining_type get_joining_type(code_point u)
         *
         *     :returns: the *Joining_Type* property of ``u``
         */
        OGONEK_UCD_GETTER(joining_type, joining_type);
        /**
         * .. function:: joining_group get_joining_group(code_point u)
         *
         *     :returns: the *Joining_Group* property of ``u``
         */
        OGONEK_UCD_GETTER(joining_group, joining_group);
        /**
         * .. function:: bool is_join_control(code_point u)
         *
         *     :returns: true if ``u`` has the *Join_Control* property; false otherwise
         */
        OGONEK_UCD_TESTER(join_control);
        /**
         * .. function:: line_break get_line_break(code_point u)
         *
         *     :returns: the *Line_Break* property of ``u``
         */
        OGONEK_UCD_GETTER(line_break, line_break);
        /**
         * .. function:: east_asian_width get_east_asian_width(code_point u)
         *
         *     :returns: the *East_Asian_Width* property of ``u``
         */
        OGONEK_UCD_GETTER(east_asian_width, east_asian_width);
        /**
         * .. function:: bool is_uppercase(code_point u)
         *
         *     :returns: true if ``u`` has the *Uppercase* property; false otherwise
         */
        OGONEK_UCD_TESTER(uppercase);
        /**
         * .. function:: bool is_lowercase(code_point u)
         *
         *     :returns: true if ``u`` has the *Lowercase* property; false otherwise
         */
        OGONEK_UCD_TESTER(lowercase);
        /**
         * .. function:: code_point get_simple_uppercase_mapping(code_point u)
         *
         *     :returns: the *Simple_Uppercase_Mapping* property of ``u``
         */
        OGONEK_UCD_CODE_POINT_GETTER(simple_uppercase_mapping);
        /**
         * .. function:: code_point get_simple_lowercase_mapping(code_point u)
         *
         *     :returns: the *Simple_Lowercase_Mapping* property of ``u``
         */
        OGONEK_UCD_CODE_POINT_GETTER(simple_lowercase_mapping);
        /**
         * .. function:: code_point get_simple_titlecase_mapping(code_point u)
         *
         *     :returns: the *Simple_Titlecase_Mapping* property of ``u``
         */
        OGONEK_UCD_CODE_POINT_GETTER(simple_titlecase_mapping);

        /**
         * .. function:: std::u32string get_uppercase_mapping(code_point u)
         *
         *     :returns: the *Uppercase_Mapping* property of ``u``
         */
        namespace fun {
            struct get_uppercase_mapping {
                std::u32string operator()(code_point u) const {
                    auto value = detail::find_property_group(uppercase_mapping_data, uppercase_mapping_data_size, u).value;
                    if(value) return value;
                    else return std::u32string(1, get_simple_uppercase_mapping{}(u));
                }
            };
        } // namespace fun
        inline namespace {
            constexpr auto const& get_uppercase_mapping = ogonek::detail::static_const<fun::get_uppercase_mapping>::value;
        }
        /**
         * .. function:: std::u32string get_lowercase_mapping(code_point u)
         *
         *     :returns: the *Lowercase_Mapping* property of ``u``
         */
        namespace fun {
            struct get_lowercase_mapping {
                std::u32string operator()(code_point u) const {
                    auto value = detail::find_property_group(lowercase_mapping_data, lowercase_mapping_data_size, u).value;
                    if(value) return value;
                    else return std::u32string(1, get_simple_lowercase_mapping{}(u));
                }
            };
        } // namespace fun
        inline namespace {
            constexpr auto const& get_lowercase_mapping = ogonek::detail::static_const<fun::get_lowercase_mapping>::value;
        }
        /**
         * .. function:: std::u32string get_titlecase_mapping(code_point u)
         *
         *     :returns: the *Titlecase_Mapping* property of ``u``
         */
        namespace fun {
            struct get_titlecase_mapping {
                std::u32string operator()(code_point u) const {
                    auto value = detail::find_property_group(titlecase_mapping_data, titlecase_mapping_data_size, u).value;
                    if(value) return value;
                    else return std::u32string(1, get_simple_titlecase_mapping{}(u));
                }
            };
        } // namespace fun
        inline namespace {
            constexpr auto const& get_titlecase_mapping = ogonek::detail::static_const<fun::get_titlecase_mapping>::value;
        }

        /**
         * .. function:: code_point get_simple_case_folding(code_point u)
         *
         *     :returns: the *Simple_Case_Folding* property of ``u``
         */
        OGONEK_UCD_CODE_POINT_GETTER(simple_case_folding);

        /**
         * .. function:: std::u32string get_case_folding(code_point u)
         *
         *     :returns: the *Case_Folding* property of ``u``
         */
        namespace fun {
            struct get_case_folding {
                std::u32string operator()(code_point u) const {
                    auto value = detail::find_property_group(case_folding_data, case_folding_data_size, u).value;
                    if(value) return value;
                    else return std::u32string(1, get_simple_case_folding{}(u));
                }
            };
        } // namespace fun
        inline namespace {
            constexpr auto const& get_case_folding = ogonek::detail::static_const<fun::get_case_folding>::value;
        }

        /**
         * .. function:: bool is_case_ignorable(code_point u)
         *
         *     :returns: true if ``u`` has the *Case_Ignorable* property; false otherwise
         */
        OGONEK_UCD_TESTER(case_ignorable);
        /**
         * .. function:: bool is_cased(code_point u)
         *
         *     :returns: true if ``u`` has the *Cased* property; false otherwise
         */
        OGONEK_UCD_TESTER(cased);
        /**
         * .. function:: bool changes_when_lowercased(code_point u)
         *
         *     :returns: true if ``u`` has the *Changes_When_Lowercased* property; false otherwise
         */
        OGONEK_UCD_QUERY(bool, changes_when_lowercased, changes_when_lowercased);
        /**
         * .. function:: bool changes_when_uppercased(code_point u)
         *
         *     :returns: true if ``u`` has the *Changes_When_Uppercased* property; false otherwise
         */
        OGONEK_UCD_QUERY(bool, changes_when_uppercased, changes_when_uppercased);
        /**
         * .. function:: bool changes_when_titlecased(code_point u)
         *
         *     :returns: true if ``u`` has the *Changes_When_Titlecased* property; false otherwise
         */
        OGONEK_UCD_QUERY(bool, changes_when_titlecased, changes_when_titlecased);
        /**
         * .. function:: bool changes_when_casefolded(code_point u)
         *
         *     :returns: true if ``u`` has the *Changes_When_Casefolded* property; false otherwise
         */
        OGONEK_UCD_QUERY(bool, changes_when_casefolded, changes_when_casefolded);
        /**
         * .. function:: bool changes_when_casemapped(code_point u)
         *
         *     :returns: true if ``u`` has the *Changes_When_Casemapped* property; false otherwise
         */
        OGONEK_UCD_QUERY(bool, changes_when_casemapped, changes_when_casemapped);
        /**
         * .. function:: bool changes_when_nfkc_casefolded(code_point u)
         *
         *     :returns: true if ``u`` has the *Changes_When_NFKC_Casefolded* property; false otherwise
         */
        OGONEK_UCD_QUERY(bool, changes_when_nfkc_casefolded, changes_when_nfkc_casefolded);

        /**
         * .. function:: std::u32string get_nfkc_casefold(code_point u)
         *
         *     :returns: the *NFKC_Casefold* property of ``u``
         */
        namespace fun {
            struct get_nfkc_casefold {
                std::u32string operator()(code_point u) const {
                    auto value = detail::find_property_group(nfkc_casefold_data, nfkc_casefold_data_size, u).value;
                    if(value) return value;
                    else return std::u32string(1, u);
                }
            };
        } // namespace fun
        inline namespace {
            constexpr auto const& get_nfkc_casefold = ogonek::detail::static_const<fun::get_nfkc_casefold>::value;
        }

        /**
         * .. function:: script get_script(code_point u)
         *
         *     :returns: the *Script* property of ``u``
         */
        OGONEK_UCD_GETTER(script, script);
        /**
         * .. function:: hangul_syllable_type get_hangul_syllable_type(code_point u)
         *
         *     :returns: the *Hangul_Syllable_Type* property of ``u``
         */
        OGONEK_UCD_GETTER(hangul_syllable_type, hangul_syllable_type);

        /**
         * .. function:: std::string get_jamo_short_name(code_point u)
         *
         *     :returns: the *Jamo_Short_Name* property of ``u``
         */
        namespace fun {
            struct get_jamo_short_name {
                std::string operator()(code_point u) const {
                    return detail::get_jamo_short_name(u);
                }
            };
        } // namespace fun
        inline namespace {
            constexpr auto const& get_jamo_short_name = ogonek::detail::static_const<fun::get_jamo_short_name>::value;
        }

        /**
         * .. function:: indic_positional_category get_indic_positional_category(code_point u)
         *
         *     :returns: the *Indic_Positional_Category* property of ``u``
         */
        OGONEK_UCD_GETTER(indic_positional_category, indic_positional_category);
        /**
         * .. function:: indic_syllabic_category get_indic_syllabic_category(code_point u)
         *
         *     :returns: the *Indic_Syllabic_Category* property of ``u``
         */
        OGONEK_UCD_GETTER(indic_syllabic_category, indic_syllabic_category);
        /**
         * .. function:: bool is_id_start(code_point u)
         *
         *     :returns: true if ``u`` has the *ID_Start* property; false otherwise
         */
        OGONEK_UCD_TESTER(id_start);
        /**
         * .. function:: bool is_id_continue(code_point u)
         *
         *     :returns: true if ``u`` has the *ID_Continue* property; false otherwise
         */
        OGONEK_UCD_TESTER(id_continue);
        /**
         * .. function:: bool is_xid_start(code_point u)
         *
         *     :returns: true if ``u`` has the *XID_Start* property; false otherwise
         */
        OGONEK_UCD_TESTER(xid_start);
        /**
         * .. function:: bool is_xid_continue(code_point u)
         *
         *     :returns: true if ``u`` has the *XID_Continue* property; false otherwise
         */
        OGONEK_UCD_TESTER(xid_continue);
        /**
         * .. function:: bool is_pattern_syntax(code_point u)
         *
         *     :returns: true if ``u`` has the *Pattern_Syntax* property; false otherwise
         */
        OGONEK_UCD_TESTER(pattern_syntax);
        /**
         * .. function:: bool is_pattern_white_space(code_point u)
         *
         *     :returns: true if ``u`` has the *Pattern_White_Space* property; false otherwise
         */
        OGONEK_UCD_TESTER(pattern_white_space);
        /**
         * .. function:: bool is_dash(code_point u)
         *
         *     :returns: true if ``u`` has the *Dash* property; false otherwise
         */
        OGONEK_UCD_TESTER(dash);
        /**
         * .. function:: bool is_quotation_mark(code_point u)
         *
         *     :returns: true if ``u`` has the *Quotation_Mark* property; false otherwise
         */
        OGONEK_UCD_TESTER(quotation_mark);
        /**
         * .. function:: bool is_terminal_punctuation(code_point u)
         *
         *     :returns: true if ``u`` has the *Terminal_Punctuation* property; false otherwise
         */
        OGONEK_UCD_TESTER(terminal_punctuation);
        /**
         * .. function:: bool is_sterm(code_point u)
         *
         *     :returns: true if ``u`` has the *STerm* property; false otherwise
         */
        OGONEK_UCD_TESTER(sterm);
        /**
         * .. function:: bool is_diacritic(code_point u)
         *
         *     :returns: true if ``u`` has the *Diacritic* property; false otherwise
         */
        OGONEK_UCD_TESTER(diacritic);
        /**
         * .. function:: bool is_extender(code_point u)
         *
         *     :returns: true if ``u`` has the *Extender* property; false otherwise
         */
        OGONEK_UCD_TESTER(extender);
        /**
         * .. function:: bool is_soft_dotted(code_point u)
         *
         *     :returns: true if ``u`` has the *Soft_Dotted* property; false otherwise
         */
        OGONEK_UCD_TESTER(soft_dotted);
        /**
         * .. function:: bool is_hex_digit(code_point u)
         *
         *     :returns: true if ``u`` has the *Hex_Digit* property; false otherwise
         */
        OGONEK_UCD_TESTER(hex_digit);
        /**
         * .. function:: bool is_ascii_hex_digit(code_point u)
         *
         *     :returns: true if ``u`` has the *ASCII_Hex_Digit* property; false otherwise
         */
        OGONEK_UCD_TESTER(ascii_hex_digit);
        /**
         * .. function:: bool is_logical_order_exception(code_point u)
         *
         *     :returns: true if ``u`` has the *Logical_Order_Exception* property; false otherwise
         */
        OGONEK_UCD_TESTER(logical_order_exception);
        /**
         * .. function:: bool is_white_space(code_point u)
         *
         *     :returns: true if ``u`` has the *White_Space* property; false otherwise
         */
        OGONEK_UCD_TESTER(white_space);
        /**
         * .. function:: bool is_variation_selector(code_point u)
         *
         *     :returns: true if ``u`` has the *Variation_Selector* property; false otherwise
         */
        OGONEK_UCD_TESTER(variation_selector);
        /**
         * .. function:: bool is_alphabetic(code_point u)
         *
         *     :returns: true if ``u`` has the *Alphabetic* property; false otherwise
         */
        OGONEK_UCD_TESTER(alphabetic);
        /**
         * .. function:: bool is_math(code_point u)
         *
         *     :returns: true if ``u`` has the *Math* property; false otherwise
         */
        OGONEK_UCD_TESTER(math);
        /**
         * .. function:: bool is_default_ignorable_code_point(code_point u)
         *
         *     :returns: true if ``u`` has the *Default_Ignorable_Code_Point* property; false otherwise
         */
        OGONEK_UCD_TESTER(default_ignorable_code_point);
        /**
         * .. function:: bool is_grapheme_base(code_point u)
         *
         *     :returns: true if ``u`` has the *Grapheme_Base* property; false otherwise
         */
        OGONEK_UCD_TESTER(grapheme_base);
        /**
         * .. function:: bool is_grapheme_extend(code_point u)
         *
         *     :returns: true if ``u`` has the *Grapheme_Extend* property; false otherwise
         */
        OGONEK_UCD_TESTER(grapheme_extend);
        /**
         * .. function:: grapheme_cluster_break get_grapheme_cluster_break(code_point u)
         *
         *     :returns: the *Grapheme_Cluster_Break* property of ``u``
         */
        OGONEK_UCD_GETTER(grapheme_cluster_break, grapheme_cluster_break);
        /**
         * .. function:: word_break get_word_break(code_point u)
         *
         *     :returns: the *Word_Break* property of ``u``
         */
        OGONEK_UCD_GETTER(word_break, word_break);
        /**
         * .. function:: sentence_break get_sentence_break(code_point u)
         *
         *     :returns: the *Sentence_Break* property of ``u``
         */
        OGONEK_UCD_GETTER(sentence_break, sentence_break);
        /**
         * .. function:: bool is_ideographic(code_point u)
         *
         *     :returns: true if ``u`` has the *Ideographic* property; false otherwise
         */
        OGONEK_UCD_TESTER(ideographic);
        /**
         * .. function:: bool is_unified_ideograph(code_point u)
         *
         *     :returns: true if ``u`` has the *Unified_Ideograph* property; false otherwise
         */
        OGONEK_UCD_TESTER(unified_ideograph);
        /**
         * .. function:: bool is_ids_binary_operator(code_point u)
         *
         *     :returns: true if ``u`` has the *IDS_Binary_Operator* property; false otherwise
         */
        OGONEK_UCD_TESTER(ids_binary_operator);
        /**
         * .. function:: bool is_ids_trinary_operator(code_point u)
         *
         *     :returns: true if ``u`` has the *IDS_Trinary_Operator* property; false otherwise
         */
        OGONEK_UCD_TESTER(ids_trinary_operator);
        /**
         * .. function:: bool is_radical(code_point u)
         *
         *     :returns: true if ``u`` has the *Radical* property; false otherwise
         */
        OGONEK_UCD_TESTER(radical);
        /**
         * .. function:: bool is_deprecated(code_point u)
         *
         *     :returns: true if ``u`` has the *Deprecated* property; false otherwise
         */
        OGONEK_UCD_TESTER(deprecated);
        /**
         * .. function:: bool is_noncharacter_code_point(code_point u)
         *
         *     :returns: true if ``u`` has the *Noncharacter_Code_Point* property; false otherwise
         */
        OGONEK_UCD_TESTER(noncharacter_code_point);

#undef OGONEK_UCD_CODE_POINT_GETTER
#undef OGONEK_UCD_TESTER3
#undef OGONEK_UCD_TESTER
#undef OGONEK_UCD_GETTER
#undef OGONEK_UCD_QUERY
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_HPP

