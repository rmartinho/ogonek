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

// Tests for encoding functions

#include <ogonek/encoding.h++>

#include <catch.hpp>
#include "util.h++"
#include "test_encodings.h++"

#include <range/v3/view/all.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/utility/functional.hpp>

#include <string>

using namespace test::string_literals;

TEST_CASE("encode", "Encoding") {
    SECTION("1to1", "Encoding one-to-one") {
        auto base = U"08AF"_s;
        auto str = ogonek::encode<test::one_to_one_encoding>(ranges::view::all(base))
                 | ranges::to_<std::u32string>();
        CHECK(str == U"19BG"_s );
    }
    SECTION("1ton", "Encoding one-to-many") {
        auto base = U"08AF\x10017"_s;
        auto str = ogonek::encode<test::one_to_many_encoding>(ranges::view::all(base))
                 | ranges::to_<std::u16string>();
        CHECK(str == u"\0" u"0\08\0A\0F\x1" u"\x17"_s);
    }
    SECTION("state", "Encoding with state") {
        auto base = U"08AF"_s;
        auto str = ogonek::encode<test::stateful_encoding>(ranges::view::all(base))
                 | ranges::to_<std::u32string>();
        CHECK(str == U"\x1234" U"08AF"_s);
    }
}
