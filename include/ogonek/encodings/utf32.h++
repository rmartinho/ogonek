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
#include <ogonek/error.h++>

namespace ogonek {
    struct utf32 {
    public:
        using code_unit = char32_t;

    private:
        static constexpr auto last_value            = 0x10FFFFu;

        static constexpr auto surrogate_mask        = 0b1111'1000'0000'0000u;
        static constexpr auto surrogate_signature   = 0b1101'1000'0000'0000u;

        static constexpr bool is_surrogate(code_unit w) {
            return (w & surrogate_mask) == surrogate_signature;
        }

    public:
        static encoded_character<utf32> encode_one(code_point u) {
            return { static_cast<code_unit>(u) };
        }

        template <typename It, typename St>
        static std::pair<code_point, It> decode_one(It first, St) {
            auto w = *first;
            if(is_surrogate(w) || w > last_value) {
                throw decode_error<utf32>();
            }
            return { static_cast<code_point>(*first), ++first };
        }
    };

    CONCEPT_ASSERT(EncodingForm<utf32>());
} // namespace ogonek

#endif // OGONEK_UTF32_HPP
