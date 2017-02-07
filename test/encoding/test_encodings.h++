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

// Test encodings

#include <ogonek/types.h++>
#include <ogonek/encoding.h++>

#include <vector>
#include <utility>

#include <cstddef>

namespace test {
    struct one_to_one_encoding {
        using code_unit = char32_t;
        static constexpr std::size_t max_width = 1;
        static std::vector<code_unit> encode_one(ogonek::code_point u) {
            return { u + 1 };
        }
        template <typename It, typename St>
        static std::pair<ogonek::code_point, It> decode_one(It first, St last) {
            return { *first - 1, ++first };
        }
    };
    CONCEPT_ASSERT(ogonek::EncodingForm<one_to_one_encoding>());
    CONCEPT_ASSERT(ogonek::StatelessEncodingForm<one_to_one_encoding>());

    struct one_to_many_encoding {
        using code_unit = char16_t;
        static constexpr std::size_t max_width = 1;
        static std::vector<code_unit> encode_one(ogonek::code_point u) {
            return { static_cast<code_unit>(u / 0x10000), static_cast<code_unit>(u % 0x10000) };
        }
        template <typename It, typename St>
        static std::pair<ogonek::code_point, It> decode_one(It first, St last) {
            ogonek::code_point u = *first++ * 0x10000;
            u += *first++;
            return { u, first };
        }
    };
    CONCEPT_ASSERT(ogonek::EncodingForm<one_to_many_encoding>());
    CONCEPT_ASSERT(ogonek::StatelessEncodingForm<one_to_many_encoding>());

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
        template <typename It, typename St>
        static std::pair<ogonek::code_point, It> decode_one(It first, St last, state& s) {
            if(not s.bom_encoded) {
                s.bom_encoded = true;
                auto bom = *first++;
                assert(bom == 0x1234);
            }
            return { *first, ++first };
        }
    };
    CONCEPT_ASSERT(ogonek::EncodingForm<stateful_encoding>());
    CONCEPT_ASSERT(not ogonek::StatelessEncodingForm<stateful_encoding>());

    // TODO encodings that need flushing
} // namespace test

