// Ogonek
//
// Written in 2017 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Tests for the UTF-8 encoding

#include <ogonek/encoding.h++>
#include <ogonek/encodings/utf8.h++>

#include <catch.hpp>
#include "util.h++"
#include "encoding/test_encodings.h++"

#include <range/v3/view/all.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/utility/functional.hpp>

#include <string>
#include <numeric>

using namespace test::string_literals;

// Based on Markus Kuhn's UTF-8 decoder capability and stress test <http://www.cl.cam.ac.uk/~mgk25/ucs/examples/UTF-8-test.txt>
TEST_CASE("UTF-8 encoding works as expected", "[encoding]") {
    SECTION("without errors") {
        test::test_encoding<ogonek::utf8>(U"\u0000\u007F\u0080\u07FF\u0800\uD7FF\uE000\uFFFF\U00010000\U0010FFFF"_s,
                                         u8"\u0000\u007F\u0080\u07FF\u0800\uD7FF\uE000\uFFFF\U00010000\U0010FFFF"_s);
    }
    SECTION("with errors") {
        auto n_continuations = [](auto count) {
            test::u8string s;
            for(auto i = 0; i < count; ++i) {
                s.push_back(i % 2? 0xBF : 0x80);
            }
            return s;
        };
        auto n_replacements = [](auto count) {
            return test::u32string(count, U'\uFFFD');
        };
        auto iota_string = [](auto start, auto count) {
            test::u8string s(count, '\0');
            std::iota(s.begin(), s.end(), start);
            return s;
        };
        auto intersperse_bytes_with_space = [](auto start, auto count) {
            test::u8string s;
            for(unsigned u = start; u < start + count; ++u) {
                s.push_back(static_cast<char>(u));
                s.push_back(' ');
            }
            return s;
        };
        auto intersperse_replacements_with_space = [](auto count) {
            test::u32string s;
            for(auto i = 0; i < count; ++i) {
                s.push_back(U'\uFFFD');
                s.push_back(U' ');
            }
            return s;
        };
        auto miss_last_byte = [](auto str) {
            str.pop_back();
            return str;
        };
        SECTION("unexpected continuation bytes") {
            test::test_decode_with_error<ogonek::utf8>(n_continuations(1), n_replacements(1), U""_s);
            test::test_decode_with_error<ogonek::utf8>(n_continuations(2), n_replacements(2), U""_s);
            test::test_decode_with_error<ogonek::utf8>(n_continuations(3), n_replacements(3), U""_s);
            test::test_decode_with_error<ogonek::utf8>(n_continuations(4), n_replacements(4), U""_s);
            test::test_decode_with_error<ogonek::utf8>(n_continuations(5), n_replacements(5), U""_s);

            auto all_continuation_bytes = iota_string(0x80, 64);
            test::test_decode_with_error<ogonek::utf8>(all_continuation_bytes, n_replacements(64), U""_s);
        }
        SECTION("lonely start characters") {
            auto all_2byte_starters_followed_by_space = intersperse_bytes_with_space(0xC0u, 32u);
            test::test_decode_with_error<ogonek::utf8>(all_2byte_starters_followed_by_space, intersperse_replacements_with_space(32), std::u32string(32, ' '));

            auto all_3byte_starters_followed_by_space = intersperse_bytes_with_space(0xE0u, 16u);
            test::test_decode_with_error<ogonek::utf8>(all_3byte_starters_followed_by_space, intersperse_replacements_with_space(16), std::u32string(16, ' '));

            auto all_4byte_starters_followed_by_space = intersperse_bytes_with_space(0xF0u, 5u);
            test::test_decode_with_error<ogonek::utf8>(all_4byte_starters_followed_by_space, intersperse_replacements_with_space(5), std::u32string(5, ' '));
        }
        SECTION("last continuation missing") {
            // TODO review number of replacement characters
            test::test_decode_with_error<ogonek::utf8>(miss_last_byte(u8"\U00000080"_s), n_replacements(1), U""_s);
            test::test_decode_with_error<ogonek::utf8>(miss_last_byte(u8"\U000007FF"_s), n_replacements(1), U""_s);
            test::test_decode_with_error<ogonek::utf8>(miss_last_byte(u8"\U00000800"_s), n_replacements(2), U""_s);
            test::test_decode_with_error<ogonek::utf8>(miss_last_byte(u8"\U0000FFFF"_s), n_replacements(2), U""_s);
            test::test_decode_with_error<ogonek::utf8>(miss_last_byte(u8"\U00010000"_s), n_replacements(3), U""_s);
            test::test_decode_with_error<ogonek::utf8>(miss_last_byte(u8"\U0010FFFF"_s), n_replacements(3), U""_s);
        }
        SECTION("concatenated incomplete sequences") {
            // TODO review number of replacement characters
            auto incompletes = miss_last_byte(u8"\U00000080"_s)
                             + miss_last_byte(u8"\U000007FF"_s)
                             + miss_last_byte(u8"\U00000800"_s)
                             + miss_last_byte(u8"\U0000FFFF"_s)
                             + miss_last_byte(u8"\U00010000"_s)
                             + miss_last_byte(u8"\U0010FFFF"_s);
            test::test_decode_with_error<ogonek::utf8>(incompletes, n_replacements(12), U""_s);
        }
        SECTION("out-of-range sequences") {
            // TODO review number of replacement characters
            test::test_decode_with_error<ogonek::utf8>(u8"\xF4\x90\x80\x80"_s, n_replacements(4), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xF4\xBF\xBF\xBF"_s, n_replacements(4), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xF5\x80\x80\x80"_s, n_replacements(4), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xF7\xBF\xBF\xBF"_s, n_replacements(4), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xF8\x80\x80\x80\x80"_s, n_replacements(5), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xFB\xBF\xBF\xBF\xBF"_s, n_replacements(5), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xFC\x80\x80\x80\x80\x80"_s, n_replacements(6), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xFD\xBF\xBF\xBF\xBF\xBF"_s, n_replacements(6), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xFE\x80\x80\x80\x80\x80\x80"_s, n_replacements(7), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xFE\xBF\xBF\xBF\xBF\xBF\xBF"_s, n_replacements(7), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xFF\x80\x80\x80\x80\x80\x80\x80"_s, n_replacements(8), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xFF\xBF\xBF\xBF\xBF\xBF\xBF\xBF"_s, n_replacements(8), U""_s);
        }
        SECTION("overlong sequences") {
            // TODO review number of replacement characters
            test::test_decode_with_error<ogonek::utf8>(u8"\xc0\x80"_s, n_replacements(2), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xc1\xBF"_s, n_replacements(2), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xE0\x80\x80"_s, n_replacements(3), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xE0\x9F\xBF"_s, n_replacements(3), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xF0\x80\x80\x80"_s, n_replacements(4), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xF0\x8F\xBF\xBF"_s, n_replacements(4), U""_s);
        }
        SECTION("surrogates") {
            // TODO review number of replacement characters
            test::test_decode_with_error<ogonek::utf8>(u8"\xED\xA0\x80"_s, n_replacements(3), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xED\xAF\xBF"_s, n_replacements(3), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xED\xB0\x80"_s, n_replacements(3), U""_s);
            test::test_decode_with_error<ogonek::utf8>(u8"\xED\xBF\xBF"_s, n_replacements(3), U""_s);
        }
        SECTION("paired surrogates") {
            // TODO review number of replacement characters
            test::test_decode_with_error<ogonek::utf8>(u8"\xED\xA0\x80\xED\xB0\x80"_s, n_replacements(6), U""_s);
        }
    }
}
