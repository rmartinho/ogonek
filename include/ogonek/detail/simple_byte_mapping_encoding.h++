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
#include <ogonek/detail/encoded_character.h++>

#include <algorithm>
#include <iterator>
#include <utility>

#include <cstddef>

namespace ogonek {
    namespace detail {
        // This is in a detail namespace because the interface uses invalid
        // code point values
        struct simple_byte_mapping {
            char b;
            char32_t u;
        };
        template <typename T>
        struct simple_byte_mapping_encoding {
            using code_unit = char;
            static constexpr std::size_t max_width = 1;

            static detail::encoded_character<simple_byte_mapping_encoding<T>> encode_one(code_point u) {
                auto it = std::find_if(std::begin(T::from_unicode), std::end(T::from_unicode), [u](auto&& m) {
                    return m.u == u;
                });
                // TODO handle errors
                return { it->b };
            }

            template <typename It, typename St>
            static std::pair<code_point, It> decode_one(It first, St) {
                auto it = std::find_if(std::begin(T::from_unicode), std::end(T::from_unicode), [b = *first](auto&& m) {
                    return m.b == b;
                });
                // TODO handle errors
                return std::make_pair(it->u, ++first);
            }
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_SIMPLE_BYTE_MAPPING
