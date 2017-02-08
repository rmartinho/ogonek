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
#include <ogonek/encodings/cp1252.h++>

#include <catch.hpp>
#include "util.h++"

#include <range/v3/view/all.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/utility/functional.hpp>

#include <string>

using namespace test::string_literals;

TEST_CASE("cp1252", "Windows-1252 encoding form") {
    SECTION("encode", "Encoding Windows-1252") {
        auto base = U"\u0041\u20AC"_s;
        auto str = ogonek::encode<ogonek::cp1252>(ranges::view::all(base))
                 | ranges::to_<test::u8string>();
        REQUIRE(str == "\x41\x80"_s);
    }
    SECTION("decode", "Decoding Windows-1252") {
        auto base = "\x41\x80"_s;
        auto str = ogonek::decode<ogonek::cp1252>(ranges::view::all(base))
                 | ranges::to_<std::u32string>();
        CHECK(str == U"\u0041\u20AC"_s);
    }
}
