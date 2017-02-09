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

// This file was automatically generated.

// UTF-8 encoding form

#ifndef OGONEK_ENCODINGS_UTF8_HPP
#define OGONEK_ENCODINGS_UTF8_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts.h++>

namespace ogonek {
    struct utf8 {
    private:
        static constexpr auto last_1byte_value       = 0x7Fu;
        static constexpr auto last_2byte_value       = 0x7FFu;
        static constexpr auto last_3byte_value       = 0xFFFFu;
        static constexpr auto last_4byte_value       = 0x10FFFFu;

        static constexpr auto byte_1of2_mask         = 0b111'1100'0000u;
        static constexpr auto byte_2of2_mask         = 0b000'0011'1111u;

        static constexpr auto byte_1of3_mask         = 0b1111'0000'0000'0000u;
        static constexpr auto byte_2of3_mask         = 0b0000'1111'1100'0000u;
        static constexpr auto byte_3of3_mask         = 0b0000'0000'0011'1111u;

        static constexpr auto byte_1of4_mask         = 0b1'1100'0000'0000'0000'0000u;
        static constexpr auto byte_2of4_mask         = 0b0'0011'1111'0000'0000'0000u;
        static constexpr auto byte_3of4_mask         = 0b0'0000'0000'1111'1100'0000u;
        static constexpr auto byte_4of4_mask         = 0b0'0000'0000'0000'0011'1111u;

        static constexpr auto continuation_mask      = 0b11'000000u;
        static constexpr auto continuation_signature = 0b10'000000u;

        static constexpr auto start_2byte_mask       = 0b111'00000u;
        static constexpr auto start_2byte_signature  = 0b110'00000u;

        static constexpr auto start_3byte_mask       = 0b1111'0000u;
        static constexpr auto start_3byte_signature  = 0b1110'0000u;

        static constexpr auto start_4byte_mask       = 0b11111'000u;
        static constexpr auto start_4byte_signature  = 0b11110'000u;

        static constexpr int sequence_length(byte b) {
            return (b & start_4byte_mask) == start_4byte_signature? 4
                 : (b & start_3byte_mask) == start_3byte_signature? 3
                 : (b & start_2byte_mask) == start_2byte_signature? 2
                 : 1;
        }

        static constexpr code_point decode(byte b0) {
            return b0;
        }
        static constexpr code_point decode(byte b0, byte b1) {
            return ((b0 & ~start_2byte_mask) << 6)
                 |  (b1 & ~continuation_mask);
        }
        static constexpr code_point decode(byte b0, byte b1, byte b2) {
            return ((b0 & ~start_3byte_mask)  << 12)
                 | ((b1 & ~continuation_mask) << 6)
                 |  (b2 & ~continuation_mask);
        }
        static constexpr code_point decode(byte b0, byte b1, byte b2, byte b3) {
            return ((b0 & ~start_4byte_mask)  << 18)
                 | ((b1 & ~continuation_mask) << 12)
                 | ((b2 & ~continuation_mask) << 6)
                 |  (b3 & ~continuation_mask);
        }

    public:
        using code_unit = char;
        static constexpr std::size_t max_width = 4;

        static std::vector<code_unit> encode_one(code_point u) {
            if(u <= last_1byte_value) {
                return { static_cast<code_unit>(u) };
            } else if(u <= last_2byte_value) {
                return {
                    static_cast<code_unit>(start_2byte_signature  | ((u & byte_1of2_mask) >> 6)),
                    static_cast<code_unit>(continuation_signature |  (u & byte_2of2_mask)),
                };
            } else if(u <= last_3byte_value) {
                return {
                    static_cast<code_unit>(start_3byte_signature  | ((u & byte_1of3_mask) >> 12)),
                    static_cast<code_unit>(continuation_signature | ((u & byte_2of3_mask) >> 6)),
                    static_cast<code_unit>(continuation_signature |  (u & byte_3of3_mask)),
                };
            }
            return {
                static_cast<code_unit>(start_4byte_signature  | ((u & byte_1of4_mask) >> 18)),
                static_cast<code_unit>(continuation_signature | ((u & byte_2of4_mask) >> 12)),
                static_cast<code_unit>(continuation_signature | ((u & byte_3of4_mask) >> 6)),
                static_cast<code_unit>(continuation_signature |  (u & byte_4of4_mask)),
            };
        }

        template <typename It, typename St>
        static std::pair<code_point, It> decode_one(It first, St) {
            byte b0 = *first++;
            auto length = sequence_length(b0);
            if(length == 1) {
                return { static_cast<code_point>(b0), first };
            }
            byte b1 = *first++;
            if(length == 2) {
                return { decode(b0, b1), first };
            }
            byte b2 = *first++;
            if(length == 3) {
                return { decode(b0, b1, b2), first };
            }
            byte b3 = *first++;
            return { decode(b0, b1, b2, b3), first };
        }
    };

    CONCEPT_ASSERT(EncodingForm<utf8>());
} // namespace ogonek

#endif // OGONEK_UTF8_HPP
