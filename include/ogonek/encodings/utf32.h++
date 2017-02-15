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

// UTF-32 encoding form

#ifndef OGONEK_ENCODINGS_UTF32_HPP
#define OGONEK_ENCODINGS_UTF32_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts.h++>
#include <ogonek/encoding.h++>

namespace ogonek {
    struct utf32 {
    public:
        using code_unit = char32_t;

        static encoded_character<utf32> encode_one(code_point u) {
            return { static_cast<code_unit>(u) };
        }

        template <typename It, typename St>
        static std::pair<code_point, It> decode_one(It first, St) {
            return { static_cast<code_point>(*first), ++first };
        }
    };

    CONCEPT_ASSERT(EncodingForm<utf32>());
} // namespace ogonek

#endif // OGONEK_UTF32_HPP
