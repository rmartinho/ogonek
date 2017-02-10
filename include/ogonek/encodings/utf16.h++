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

// UTF-16 encoding form

#ifndef OGONEK_ENCODINGS_UTF16_HPP
#define OGONEK_ENCODINGS_UTF16_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts.h++>
#include <ogonek/detail/encoded_character.h++>

namespace ogonek {
    struct utf16 {
    public:
        using code_unit = char16_t;

    private:
        static constexpr auto last_1word_value          = 0xFFFFu;
        static constexpr auto last_2word_value          = 0x10FFFFu;

        static constexpr auto word_1of2_mask            = 0b1111'1111'1100'0000'0000u;
        static constexpr auto word_2of2_mask            = 0b0000'0000'0011'1111'1111u;

        static constexpr auto surrogate_mask            = 0b1111'1100'0000'0000u;
        static constexpr auto lead_surrogate_signature  = 0b1101'1000'0000'0000u;
        static constexpr auto trail_surrogate_signature = 0b1101'1100'0000'0000u;

        static constexpr auto surrogate_delta           = 0x10000u;
        static constexpr auto surrogate_shift           = 10;

        static constexpr int sequence_length(code_unit w) {
            return (w & surrogate_mask) == lead_surrogate_signature? 2 : 1;
        }

        static constexpr code_point decode(code_unit w0) {
            return w0;
        }
        static constexpr code_point decode(code_unit w0, code_unit w1) {
            return surrogate_delta
                + ((w0 & ~surrogate_mask) << 1 * surrogate_shift)
                | ((w1 & ~surrogate_mask) << 0 * surrogate_shift);
        }

    public:
        static constexpr std::size_t max_width = 2;

        static detail::encoded_character<utf16> encode_one(code_point u) {
            if(u <= last_1word_value) {
                return { static_cast<code_unit>(u) };
            }
            auto adjusted = u - surrogate_delta;
            return {
                static_cast<code_unit>(lead_surrogate_signature  | ((adjusted & word_1of2_mask) >> 1 * surrogate_shift)),
                static_cast<code_unit>(trail_surrogate_signature | ((adjusted & word_2of2_mask) >> 0 * surrogate_shift)),
            };
        }

        template <typename It, typename St>
        static std::pair<code_point, It> decode_one(It first, St) {
            code_unit w0 = *first++;
            auto length = sequence_length(w0);
            if(length == 1) {
                return { static_cast<code_point>(w0), first };
            }
            code_unit w1 = *first++;
            return { decode(w0, w1), first };
        }
    };

    CONCEPT_ASSERT(EncodingForm<utf16>());
} // namespace ogonek

#endif // OGONEK_UTF16_HPP
