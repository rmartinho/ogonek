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

TEST_CASE("encoding and decoding works as expected", "[encoding]") {
    SECTION("one-to-one") {
        test::test_encoding<test::one_to_one_encoding>( U"08AF"_s,        U"19BG"_s);
    }
    SECTION("one-to-many") {
        test::test_encoding<test::one_to_many_encoding>(U"08AF\x10017"_s, u"\0" u"0\08\0A\0F\x1" u"\x17"_s);
    }
    SECTION("stateful") {
        test::test_encoding<test::stateful_encoding>(   U"08AF"_s,        U"\x1234" U"08AF"_s);
    }
}
