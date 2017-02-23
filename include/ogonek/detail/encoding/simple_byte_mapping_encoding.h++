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

// Codepage-style encodings

#ifndef OGONEK_DETAIL_SIMPLE_BYTE_MAPPING
#define OGONEK_DETAIL_SIMPLE_BYTE_MAPPING

#include <ogonek/types.h++>
#include <ogonek/encoding.h++>
#include <ogonek/error.h++>

#include <algorithm>
#include <iterator>
#include <utility>

#include <cstddef>

namespace ogonek {
    namespace detail {
        // This is in a detail namespace because the interface uses invalid
        // code point values TODO replace all such misuses with optional<code_point>
        struct simple_byte_mapping {
            char b;
            char32_t u;
        };
        template <typename T, char32_t Replacement = U'\uFFFD'>
        struct simple_byte_mapping_encoding {
            using code_unit = char;
            static constexpr auto replacement_character = Replacement;

            static coded_character<simple_byte_mapping_encoding> encode_one(code_point u) {
                auto it = std::find_if(std::begin(T::from_unicode), std::end(T::from_unicode), [u](auto&& m) {
                    return m.u == u;
                });
                if(it != std::end(T::from_unicode)) {
                    return { it->b };
                } else {
                    throw encode_error<simple_byte_mapping_encoding>();
                }
            }

            template <typename It, typename St>
            static std::pair<code_point, It> decode_one(It first, St) {
                auto it = std::find_if(std::begin(T::from_unicode), std::end(T::from_unicode), [b = *first](auto&& m) {
                    return m.b == b;
                });
                if(it != std::end(T::from_unicode)) {
                    return std::make_pair(it->u, ++first);
                } else {
                    throw decode_error<simple_byte_mapping_encoding>();
                }
            }
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_SIMPLE_BYTE_MAPPING
