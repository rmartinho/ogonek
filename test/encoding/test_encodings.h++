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
#include <ogonek/error.h++>
#include <ogonek/encoding.h++>
#include <ogonek/detail/simple_byte_mapping_encoding.h++>
#include <ogonek/detail/container/optional.h++>

#include <catch.hpp>
#include "util.h++"

#include <vector>
#include <utility>

#include <cstddef>

namespace test {
    struct one_to_one_encoding {
        using code_unit = char32_t;
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

    struct custom_replacement_encoding {
        using code_unit = char32_t;
        static constexpr auto replacement_character = U'\uE001';
        static std::vector<code_unit> encode_one(ogonek::code_point u) {
            return { u };
        }
        template <typename It, typename St>
        static std::pair<ogonek::code_point, It> decode_one(It first, St last) {
            return { *first, ++first };
        }
    };
    CONCEPT_ASSERT(ogonek::EncodingForm<custom_replacement_encoding>());

    template <typename T = void>
    struct basic_codepage {
        static ogonek::code_point to_unicode[256];
        static ogonek::detail::simple_byte_mapping from_unicode[128];
    };

    struct basic_codepage_encoding : public ogonek::detail::simple_byte_mapping_encoding<basic_codepage<>> {
    public:
        static constexpr auto replacement_character = U'\u0080';
    };

    CONCEPT_ASSERT(ogonek::EncodingForm<basic_codepage_encoding>());
    CONCEPT_ASSERT(ogonek::StatelessEncodingForm<basic_codepage_encoding>());

    template <typename E, typename Dec, typename Enc>
    void test_encoding(Dec dec, Enc enc) {
        CONCEPT_ASSERT(ogonek::EncodingForm<E>());

        SECTION("encode") {
            auto str = ogonek::encode<E>(ranges::view::all(dec), ogonek::throw_error)
                     | ranges::to_<Enc>();
            REQUIRE(str == enc);
        }
        SECTION("decode") {
            auto str = ogonek::decode<E>(ranges::view::all(enc), ogonek::throw_error)
                     | ranges::to_<Dec>();
            REQUIRE(str == dec);
        }
    }

    template <typename E, typename Dec, typename Enc>
    void test_encode_with_error(Dec dec, Enc enc) {
        CONCEPT_ASSERT(ogonek::EncodingForm<E>());

        SECTION("encode with error") {
            auto str = ogonek::encode<E>(ranges::view::all(dec), ogonek::replace_errors)
                     | ranges::to_<Enc>();
            REQUIRE(str == enc);
        }
    }

    template <typename E, typename Enc, typename Dec>
    void test_decode_with_error(Enc enc, Dec dec) {
        SECTION("decode with error") {
            auto str = ogonek::decode<E>(ranges::view::all(enc), ogonek::replace_errors)
                     | ranges::to_<Dec>();
            REQUIRE(str == dec);
        }
    }

    // TODO encodings that need flushing

    template <typename T>
    ogonek::code_point basic_codepage<T>::to_unicode[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
        33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
        49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
        65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
        81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
        97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112,
        113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    };

    template <typename T>
    ogonek::detail::simple_byte_mapping basic_codepage<T>::from_unicode[] = {
        { static_cast<char>(0), 1 }, { static_cast<char>(1), 2 }, { static_cast<char>(2), 3 }, { static_cast<char>(3), 4 },
        { static_cast<char>(4), 5 }, { static_cast<char>(5), 6 }, { static_cast<char>(6), 7 }, { static_cast<char>(7), 8 },
        { static_cast<char>(8), 9 }, { static_cast<char>(9), 10 }, { static_cast<char>(10), 11 }, { static_cast<char>(11), 12 },
        { static_cast<char>(12), 13 }, { static_cast<char>(13), 14 }, { static_cast<char>(14), 15 }, { static_cast<char>(15), 16 },
        { static_cast<char>(16), 17 }, { static_cast<char>(17), 18 }, { static_cast<char>(18), 19 }, { static_cast<char>(19), 20 },
        { static_cast<char>(20), 21 }, { static_cast<char>(21), 22 }, { static_cast<char>(22), 23 }, { static_cast<char>(23), 24 },
        { static_cast<char>(24), 25 }, { static_cast<char>(25), 26 }, { static_cast<char>(26), 27 }, { static_cast<char>(27), 28 },
        { static_cast<char>(28), 29 }, { static_cast<char>(29), 30 }, { static_cast<char>(30), 31 }, { static_cast<char>(31), 32 },
        { static_cast<char>(32), 33 }, { static_cast<char>(33), 34 }, { static_cast<char>(34), 35 }, { static_cast<char>(35), 36 },
        { static_cast<char>(36), 37 }, { static_cast<char>(37), 38 }, { static_cast<char>(38), 39 }, { static_cast<char>(39), 40 },
        { static_cast<char>(40), 41 }, { static_cast<char>(41), 42 }, { static_cast<char>(42), 43 }, { static_cast<char>(43), 44 },
        { static_cast<char>(44), 45 }, { static_cast<char>(45), 46 }, { static_cast<char>(46), 47 }, { static_cast<char>(47), 48 },
        { static_cast<char>(48), 49 }, { static_cast<char>(49), 50 }, { static_cast<char>(50), 51 }, { static_cast<char>(51), 52 },
        { static_cast<char>(52), 53 }, { static_cast<char>(53), 54 }, { static_cast<char>(54), 55 }, { static_cast<char>(55), 56 },
        { static_cast<char>(56), 57 }, { static_cast<char>(57), 58 }, { static_cast<char>(58), 59 }, { static_cast<char>(59), 60 },
        { static_cast<char>(60), 61 }, { static_cast<char>(61), 62 }, { static_cast<char>(62), 63 }, { static_cast<char>(63), 64 },
        { static_cast<char>(64), 65 }, { static_cast<char>(65), 66 }, { static_cast<char>(66), 67 }, { static_cast<char>(67), 68 },
        { static_cast<char>(68), 69 }, { static_cast<char>(69), 70 }, { static_cast<char>(70), 71 }, { static_cast<char>(71), 72 },
        { static_cast<char>(72), 73 }, { static_cast<char>(73), 74 }, { static_cast<char>(74), 75 }, { static_cast<char>(75), 76 },
        { static_cast<char>(76), 77 }, { static_cast<char>(77), 78 }, { static_cast<char>(78), 79 }, { static_cast<char>(79), 80 },
        { static_cast<char>(80), 81 }, { static_cast<char>(81), 82 }, { static_cast<char>(82), 83 }, { static_cast<char>(83), 84 },
        { static_cast<char>(84), 85 }, { static_cast<char>(85), 86 }, { static_cast<char>(86), 87 }, { static_cast<char>(87), 88 },
        { static_cast<char>(88), 89 }, { static_cast<char>(89), 90 }, { static_cast<char>(90), 91 }, { static_cast<char>(91), 92 },
        { static_cast<char>(92), 93 }, { static_cast<char>(93), 94 }, { static_cast<char>(94), 95 }, { static_cast<char>(95), 96 },
        { static_cast<char>(96), 97 }, { static_cast<char>(97), 98 }, { static_cast<char>(98), 99 }, { static_cast<char>(99), 100 },
        { static_cast<char>(100), 101 }, { static_cast<char>(101), 102 }, { static_cast<char>(102), 103 }, { static_cast<char>(103), 104 },
        { static_cast<char>(104), 105 }, { static_cast<char>(105), 106 }, { static_cast<char>(106), 107 }, { static_cast<char>(107), 108 },
        { static_cast<char>(108), 109 }, { static_cast<char>(109), 110 }, { static_cast<char>(110), 111 }, { static_cast<char>(111), 112 },
        { static_cast<char>(112), 113 }, { static_cast<char>(113), 114 }, { static_cast<char>(114), 115 }, { static_cast<char>(115), 116 },
        { static_cast<char>(116), 117 }, { static_cast<char>(117), 118 }, { static_cast<char>(118), 119 }, { static_cast<char>(119), 120 },
        { static_cast<char>(120), 121 }, { static_cast<char>(121), 122 }, { static_cast<char>(122), 123 }, { static_cast<char>(123), 124 },
        { static_cast<char>(124), 125 }, { static_cast<char>(125), 126 }, { static_cast<char>(126), 127 }, { static_cast<char>(127), 128 },
    };
} // namespace test
