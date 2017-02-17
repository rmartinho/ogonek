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

// Tests for the error handlers

#include <ogonek/error.h++>

#include <catch.hpp>
#include "util.h++"
#include "encoding/test_encodings.h++"

using namespace test::string_literals;

TEST_CASE("discard_errors discards errors", "[error]") {
    SECTION("encode_error") {
        auto r = ogonek::discard_errors(ogonek::encode_error<test::one_to_one_encoding>());
        CHECK_FALSE(static_cast<bool>(r));
    }
    SECTION("decode_error") {
        auto r = ogonek::discard_errors(ogonek::decode_error<test::one_to_one_encoding>());
        CHECK_FALSE(static_cast<bool>(r));
    }
}

TEST_CASE("replace_errors replaces errors", "[error]") {
    SECTION("encode_error, default replacement") {
        auto r = ogonek::replace_errors(ogonek::encode_error<test::one_to_one_encoding>());
        REQUIRE(static_cast<bool>(r));
        CHECK(*r == U'\uFFFD');
    }
    SECTION("encode_error, custom replacement") {
        auto r = ogonek::replace_errors(ogonek::encode_error<test::custom_replacement_encoding>());
        REQUIRE(static_cast<bool>(r));
        CHECK(*r == ogonek::replacement_character_v<test::custom_replacement_encoding>);
    }
    SECTION("decode_error, default replacement") {
        auto r = ogonek::replace_errors(ogonek::decode_error<test::one_to_one_encoding>());
        REQUIRE(static_cast<bool>(r));
        CHECK(*r == U'\uFFFD');
    }
    SECTION("decode_error, custom replacement doesn't matter") {
        auto r = ogonek::replace_errors(ogonek::decode_error<test::custom_replacement_encoding>());
        REQUIRE(static_cast<bool>(r));
        CHECK(*r == U'\uFFFD');
    }
}

TEST_CASE("throw_error throws errors", "[error]") {
    SECTION("encode_error") {
        CHECK_THROWS_AS(ogonek::throw_error(ogonek::encode_error<test::one_to_one_encoding>()),
                        ogonek::encode_error<test::one_to_one_encoding>);
    }
    SECTION("decode_error") {
        CHECK_THROWS_AS(ogonek::throw_error(ogonek::decode_error<test::one_to_one_encoding>()),
                        ogonek::decode_error<test::one_to_one_encoding>);
    }
}
