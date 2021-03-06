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

// Tests utilities

#ifndef TEST_UTIL_HPP
#define TEST_UTIL_HPP

#include <ogonek/types.h++>

#include <catch.hpp>

#include <sstream>
#include <vector>
#include <string>
#include <type_traits>

#include <cstddef>

namespace test {
    namespace detail {
        template <typename T>
        void format_code_unit(std::ostream& os, T u) {
            os.width(2*sizeof(T));
            os.fill('0');
            os << std::hex << std::uppercase << static_cast<unsigned long long>(static_cast<std::make_unsigned_t<T>>(u));
        }
        template <typename T>
        void format_code_point(std::ostream& os, T u) {
            os << "U+";
            os.width(4);
            os.fill('0');
            os << std::hex << std::uppercase << static_cast<unsigned>(u);
        }
        template <typename T, typename Str>
        std::string convert_string(Str const& str, void (*formatter)(std::ostream&, T)) {
            std::stringstream ss;
            bool is_first = true;
            ss << '<';
            for(auto u : str) {
                if(!is_first) ss << ' ';
                formatter(ss, u);
                is_first = false;
            }
            ss << '>';
            return ss.str();
        }
        template <typename T>
        struct code_unit_converter {
            static std::string convert(std::vector<T> const& str) {
                return convert_string<T>(str, &format_code_unit);
            }
            static std::string convert(std::basic_string<T> const& str) {
                return convert_string<T>(str, &format_code_unit);
            }
        };
        struct code_point_converter {
            static std::string convert(std::u32string const& str) {
                return convert_string<char32_t>(str, &format_code_point);
            }
        };
        template <typename T>
        struct optional_converter {
            static std::string convert(ogonek::optional<T> const& opt) {
                if(opt) {
                    return Catch::StringMaker<T>::convert(*opt);
                } else {
                    return "<none>";
                }
            }
        };
    } // namespace detail

    struct u8string : std::string {
        using std::string::string;
    };
    using std::u16string;
    using std::u32string;

    namespace string_literals {
        inline u8string operator ""_s(const char *str, std::size_t len) {
            return { str, len };
        }

        inline std::u16string operator ""_s(const char16_t *str, std::size_t len) {
            return { str, len };
        }

        inline std::u32string operator ""_s(const char32_t *str, std::size_t len) {
            return { str, len };
        }
    }
} // namespace test

namespace Catch {
    template <>
    struct StringMaker<std::vector<char32_t>> : ::test::detail::code_unit_converter<char32_t> {};
    template <>
    struct StringMaker<std::vector<char16_t>> : ::test::detail::code_unit_converter<char16_t> {};
    template <>
    struct StringMaker<std::vector<char>> : ::test::detail::code_unit_converter<char> {};
    template <>
    struct StringMaker<::test::u8string> : ::test::detail::code_unit_converter<char> {};
    template <>
    struct StringMaker<std::u16string> : ::test::detail::code_unit_converter<char16_t> {};
    template <>
    struct StringMaker<std::u32string> : ::test::detail::code_point_converter {};
    template <typename T>
    struct StringMaker<::ogonek::optional<T>> : ::test::detail::optional_converter<T> {};
} // namespace Catch

#endif // TEST_UTIL_HPP
