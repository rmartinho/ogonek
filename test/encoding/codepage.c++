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

// Tests for the Windows-1252 encoding

#include <ogonek/encoding.h++>
#include <ogonek/error.h++>

#include <catch.hpp>
#include "util.h++"
#include "encoding/test_encodings.h++"

#include <range/v3/view/all.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/utility/functional.hpp>

#include <string>

using namespace test::string_literals;

TEST_CASE("encoding and decoding codepages works as expected", "[encoding][codepage]") {
    SECTION("without errors") {
        test::test_encoding<test::basic_codepage_encoding>(U"\u0001\u0002\u0003\u0080"_s, "\x0\x1\x2\x7F"_s);
    }
    SECTION("with errors") {
        test::test_encode_with_error<test::basic_codepage_encoding>(U"\u0001\u0002\u0003\u1000\u007F\u0080"_s, "\x0\x1\x2\x7F\x7E\x7F"_s);

        //test::test_decode_with_error<test::basic_codepage_encoding>("\x0\x1\x2\x80\x7E\x7F"_s, U"\u0001\u0002\u0003\uFFFD\u007F\u0080"_s);
    }
}
