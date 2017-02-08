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
#include <ogonek/encodings/cp1251.h++>
#include <ogonek/encodings/cp1252.h++>

#include <catch.hpp>
#include "util.h++"
#include "test_encodings.h++"

#include <range/v3/view/all.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/utility/functional.hpp>

#include <string>

using namespace test::string_literals;

TEST_CASE("codepage", "Codepage-based encodings") {
    SECTION("encode", "Encoding") {
        auto base = U"\u0001\u0002\u0003\u0100"_s;
        auto str = ogonek::encode<test::basic_codepage_encoding>(ranges::view::all(base))
                | ranges::to_<test::u8string>();
        REQUIRE(str == "\x0\x1\x2\xFF"_s);
    }
    SECTION("decode", "Decoding") {
        auto base = "\x0\x1\x2\xFF"_s;
        auto str = ogonek::decode<test::basic_codepage_encoding>(ranges::view::all(base))
                | ranges::to_<std::u32string>();
        CHECK(str == U"\u0001\u0002\u0003\u0100"_s);
    }
}
