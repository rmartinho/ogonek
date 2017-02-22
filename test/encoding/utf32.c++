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

// Tests for the UTF-32 encoding

#include <ogonek/encoding.h++>
#include <ogonek/encodings/utf32.h++>

#include <catch.hpp>
#include "util.h++"
#include "encoding/test_encodings.h++"

#include <range/v3/view/all.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/utility/functional.hpp>

#include <string>

using namespace test::string_literals;

TEST_CASE("UTF-32 encoding works as expected", "[encoding]") {
    SECTION("without errors") {
        test::test_encoding<ogonek::utf32>(U"\u0000\uD7FF\uE000\uFFFF\U00010000\U0010FFFF"_s,
                                           U"\u0000\uD7FF\uE000\uFFFF\U00010000\U0010FFFF"_s);
    }
    SECTION("with errors") {
        SECTION("surrogates") {
            test::test_decode_with_error<ogonek::utf32>(U"\u1234\xD800\u5678\xDFFF\u4321"_s, U"\u1234\uFFFD\u5678\uFFFD\u4321"_s, U"\u1234\u5678\u4321"_s);
        }
        SECTION("out of range") {
            test::test_decode_with_error<ogonek::utf32>(U"\u1234\xffffffff\u5678\x110000\u4321"_s, U"\u1234\uFFFD\u5678\uFFFD\u4321"_s, U"\u1234\u5678\u4321"_s);
        }
    }
}

