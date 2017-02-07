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

// Tests for decoding functions

#include <ogonek/encoding.h++>

#include <catch.hpp>
#include "util.h++"
#include "test_encodings.h++"

#include <range/v3/view/all.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/utility/functional.hpp>

#include <string>

using namespace test::string_literals;

TEST_CASE("decode", "Decoding") {
    SECTION("1to1", "Decoding one-to-one") {
        auto base = U"19BG"_s;
        auto str = ogonek::decode<test::one_to_one_encoding>(ranges::view::all(base))
                 | ranges::to_<std::u32string>();
        CHECK(str == U"08AF"_s );
    }
    SECTION("1ton", "Decoding one-to-many") {
        auto base = u"\0" u"0\08\0A\0F\x1" u"\x17"_s;
        auto str = ogonek::decode<test::one_to_many_encoding>(ranges::view::all(base))
                 | ranges::to_<std::u32string>();
        CHECK(str == U"08AF\x10017"_s);
    }
    SECTION("state", "Decoding with state") {
        auto base = U"\x1234" U"08AF"_s;
        auto str = ogonek::decode<test::stateful_encoding>(ranges::view::all(base))
                 | ranges::to_<std::u32string>();
        CHECK(str == U"08AF"_s);
    }
}
