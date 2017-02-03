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

// Tests for <ogonek/encode.h++>

#include <ogonek/encode.h++>

#include <catch.hpp>
#include "util.h++"

#include <range/v3/view/all.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/utility/functional.hpp>

#include <vector>

#include <cstddef>

namespace test {
    struct one_to_one_encoding {
        using code_unit = char32_t;
        static constexpr std::size_t max_width = 1;
        static std::vector<code_unit> encode_one(ogonek::code_point u) {
            return { u + 1 };
        }
    };
    struct one_to_many_encoding {
        using code_unit = char16_t;
        static constexpr std::size_t max_width = 1;
        static std::vector<code_unit> encode_one(ogonek::code_point u) {
            return { static_cast<code_unit>(u / 0x10000), static_cast<code_unit>(u % 0x10000) };
        }
    };
    struct stateful_encoding {
        using code_unit = char32_t;
        struct state { bool bom_encoded = false; };
        static constexpr std::size_t max_width = 1;
        static std::vector<code_unit> encode_one(ogonek::code_point u, state& s) {
            if(not s.bom_encoded) {
                s.bom_encoded = true;
                return { 0x1234, u };
            } else {
                return { u };
            }
        }
    };
    CONCEPT_ASSERT(ogonek::EncodingForm<one_to_one_encoding>());
    CONCEPT_ASSERT(ogonek::EncodingForm<one_to_many_encoding>());
    CONCEPT_ASSERT(ogonek::EncodingForm<stateful_encoding>());
} // namespace test

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