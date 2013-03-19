// Ogonek
//
// Written in 2012-2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Unicode text segmentation algorithms (UAX #29)

#ifndef OGONEK_SEGMENTATION_HPP
#define OGONEK_SEGMENTATION_HPP

#include <ogonek/types.h++>
#include <ogonek/ucd.h++>
#include <ogonek/detail/lookahead_window.h++>
#include <ogonek/detail/ranges.h++>

#include <wheels/enums.h++>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/sub_range.hpp>

#include <algorithm>
#include <iterator>
#include <type_traits>

namespace ogonek {
    namespace detail {
        using gcb = ucd::grapheme_cluster_break;
        struct grapheme_cluster_rule {
            gcb before;
            bool is_break;
            gcb after;

            bool matches(code_point before, code_point after) const;
        };
    } // namespace detail
} // namespace ogonek

namespace wheels {
    template <>
    struct is_flags<ogonek::detail::gcb> : std::true_type {};
} // namespace wheels

namespace ogonek {
    namespace detail {
        constexpr gcb gcb_any = static_cast<gcb>(0xFFFFFFFFu);
        constexpr grapheme_cluster_rule operator*(gcb l, gcb r) { return { l, false, r }; }
        constexpr grapheme_cluster_rule operator/(gcb l, gcb r) { return { l, true, r }; }

        // TODO: switch to a pair table instead
        constexpr grapheme_cluster_rule grapheme_cluster_rules[] = {
            // Break at the start and end of text.
            // * Handled specially
            // Do not break between a CR and LF. Otherwise, break before and after controls.
            /* GB3. */                       gcb::CR * gcb::LF,
            /* GB4. */ (gcb::CN | gcb::CR | gcb::LF) / gcb_any,
            /* GB5. */                       gcb_any / (gcb::CN | gcb::CR | gcb::LF),
            // Do not break Hangul syllable sequences.
            /* GB6. */                        gcb::L * (gcb::L | gcb::V | gcb::LV | gcb::LVT),
            /* GB7. */            (gcb::LV | gcb::V) * (gcb::V | gcb::T),
            /* GB8. */           (gcb::LVT | gcb::T) * gcb::T,
            // Do not break between regional indicator symbols.
            /* GB8a. */                      gcb::RI * gcb::RI,
            // Do not break before extending characters.
            /* GB9. */                       gcb_any * gcb::EX,
            // Do not break before SpacingMarks, or after Prepend characters.
            /* GB9a. */                      gcb_any * gcb::SM,
            /* GB9b. */                      gcb::PP * gcb_any,
            // Otherwise, break everywhere.
            /* GB10. */                      gcb_any / gcb_any,
        };
        inline bool grapheme_cluster_rule::matches(code_point before, code_point after) const {
            const gcb none = static_cast<gcb>(0);
            return (ucd::get_grapheme_cluster_break(before) & this->before) != none
                && (ucd::get_grapheme_cluster_break(after) & this->after) != none;
        }
        inline bool is_grapheme_cluster_boundary(code_point before, code_point after) {
            return std::find_if(std::begin(grapheme_cluster_rules), std::end(grapheme_cluster_rules),
                                [before, after](grapheme_cluster_rule const& rule) {
                                    return rule.matches(before, after);
                                })
                   ->is_break;
        }
    } // namespace detail

    template <typename CodePointIterator>
    struct grapheme_cluster_iterator
    : boost::iterator_facade<
        grapheme_cluster_iterator<CodePointIterator>,
        boost::iterator_range<CodePointIterator>,
        std::input_iterator_tag, // TODO
        boost::iterator_range<CodePointIterator>>
    {
    public:
        grapheme_cluster_iterator(CodePointIterator first, CodePointIterator last)
        : first(first), last(last) {}

    private:
        friend class boost::iterator_core_access;

        boost::iterator_range<CodePointIterator> dereference() const {
            auto begin = first;
            auto it = first;
            auto before = *it++;
            do {
                auto after = *it;
                if(detail::is_grapheme_cluster_boundary(before, after)) break;
                ++it;
                if(it == last) break;
                before = after;
            } while(true);
            return boost::iterator_range<CodePointIterator> { begin, it };
        }
        void increment() {
            first = dereference().end();
        }
        bool equal(grapheme_cluster_iterator const& that) const {
            return first == that.first;
        }

        CodePointIterator first;
        CodePointIterator last;
    };

    template <typename UnicodeSequence,
              typename Iterator = grapheme_cluster_iterator<detail::RangeConstIterator<UnicodeSequence>>>
    boost::iterator_range<Iterator> grapheme_clusters(UnicodeSequence const& sequence) {
        return detail::wrap_range<Iterator>(detail::as_code_point_range(sequence, skip_validation));
    }

    namespace detail {
        using wb = ucd::word_break;
        struct word_rule {
            wb before1;
            wb before0;
            bool is_break;
            wb after0;
            wb after1;

            bool matches(code_point before1, code_point before0, code_point after0, code_point after1) const;
        };
    } // namespace detail
} // namespace ogonek

namespace wheels {
    template <>
    struct is_flags<ogonek::detail::wb> : std::true_type {};
} // namespace wheels

namespace ogonek {
    namespace detail {
        constexpr wb wb_any = static_cast<wb>(0xFFFFFFFFu);
        struct wb_seq {
            wb first;
            wb second;
        };
        constexpr wb_seq operator+(wb l, wb r) { return { l, r }; }
        constexpr word_rule operator*(wb l, wb r) { return { wb_any, l, false, r, wb_any }; }
        constexpr word_rule operator*(wb_seq l, wb r) { return { l.first, l.second, false, r, wb_any }; }
        constexpr word_rule operator*(wb l, wb_seq r) { return { wb_any, l, false, r.first, r.second }; }
        constexpr word_rule operator/(wb l, wb r) { return { wb_any, l, true,  r, wb_any }; }

        // TODO: switch to a pair table instead
        constexpr word_rule word_rules[] = {
            // Break at the start and end of text.
            // * Handled specially
            // Do not break within CRLF.
            /* WB3. */                                wb::CR * wb::LF,
            /* WB3a. */           (wb::NL | wb::CR | wb::LF) / wb_any,
            /* WB3b. */                               wb_any / (wb::NL | wb::CR | wb::LF),
            // Ignore Format and Extend characters, except when they appear at the beginning of a region of text.
            /* WB4. */           ~(wb::NL | wb::CR | wb::LF) * (wb::Extend | wb::FO),
            // Do not break between most letters.
            /* WB5. */                                wb::LE * wb::LE,
            // Do not break letters across certain punctuation.
            /* WB6. */                                wb::LE * ((wb::ML | wb::MB) + wb::LE),
            /* WB7. */          (wb::LE + (wb::ML | wb::MB)) * wb::LE,
            // Do not break within sequences of digits, or digits adjacent to letters ("3a", or "A3").
            /* WB8. */                                wb::NU * wb::NU,
            /* WB9. */                                wb::LE * wb::NU,
            /* WB10. */                               wb::NU * wb::LE,
            // Do not break within sequences, such as "3.2" or "3,456.789".
            /* WB11. */         (wb::NU + (wb::MN | wb::MB)) * wb::NU,
            /* WB12. */                               wb::NU * ((wb::MN | wb::MB) + wb::NU),
            // Do not break between Katakana.
            /* WB13. */                               wb::KA * wb::KA,
            // Do not break from extenders.
            /* WB13a. */ (wb::LE | wb::NU | wb::KA | wb::EX) * wb::EX,
            /* WB13b. */                              wb::EX * (wb::LE | wb::NU | wb::KA | wb::EX),
            // Do not break between regional indicator symbols.
            /* WB13c. */                              wb::RI * wb::RI,
            // Otherwise, break everywhere (including around ideographs).
            /* WB14. */                               wb_any / wb_any,
        };
        inline bool word_rule::matches(code_point before1, code_point before0, code_point after0, code_point after1) const {
            const wb none = static_cast<wb>(0);
            return (this->before1 == wb_any || (before1 != -1u && (ucd::get_word_break(before1) & this->before1) != none))
                && (ucd::get_word_break(before0) & this->before0) != none
                && (ucd::get_word_break(after0) & this->after0) != none
                && (this->after1 == wb_any || (after1 != -1u && (ucd::get_word_break(after1) & this->after1) != none));
        }
        inline bool is_word_boundary(code_point before1, code_point before0, code_point after0, code_point after1) {
            return std::find_if(std::begin(word_rules), std::end(word_rules),
                                [before1, before0, after0, after1](word_rule const& rule) {
                                    return rule.matches(before1, before0, after0, after1);
                                })
                   ->is_break;
        }
        inline bool should_skip_in_word(code_point before, code_point after) {
            return before != -1u && after != -1u &&
                word_rules[3].matches(-1, before, after, -1);
                //|| word_rules[3].matches(-1, after, before, -1));
        }
    } // namespace detail
    template <typename CodePointIterator>
    struct word_iterator
    : boost::iterator_facade<
        word_iterator<CodePointIterator>,
        boost::iterator_range<CodePointIterator>,
        std::input_iterator_tag, // TODO
        boost::iterator_range<CodePointIterator>>
    {
    public:
        word_iterator(CodePointIterator first, CodePointIterator last)
        : first(first), last(last) {}

    private:
        friend class boost::iterator_core_access;

        boost::iterator_range<CodePointIterator> dereference() const {
            detail::lookahead_window<CodePointIterator, 2, 2> window(first, last);

            do {
                while(detail::should_skip_in_word(window[-1], window[0])) {
                    window.skip(0);
                }
                while(detail::should_skip_in_word(window[0], window[1])) {
                    window.skip(1);
                }
                while(detail::should_skip_in_word(window[1], window[2])) {
                    window.skip(2);
                }
                if(detail::is_word_boundary(window[-2], window[-1], window[0], window[1])) break;
                window.advance();
            } while(true);
            return boost::iterator_range<CodePointIterator> { first, window.position() };
        }
        void increment() {
            first = dereference().end();
        }
        bool equal(word_iterator const& that) const {
            return first == that.first;
        }

        CodePointIterator first;
        CodePointIterator last;
    };

    template <typename UnicodeSequence,
              typename Iterator = word_iterator<detail::RangeConstIterator<UnicodeSequence>>>
    boost::iterator_range<Iterator> words(UnicodeSequence const& sequence) {
        return detail::wrap_range<Iterator>(detail::as_code_point_range(sequence, skip_validation));
    }
} // namespace ogonek

#endif // OGONEK_SEGMENTATION_HPP
