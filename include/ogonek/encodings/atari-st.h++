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

// AtariST encoding form

#ifndef OGONEK_ENCODINGS_ATARI_ST_HPP
#define OGONEK_ENCODINGS_ATARI_ST_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts.h++>
#include <ogonek/detail/encoding/simple_byte_mapping_encoding.h++>
#include <ogonek/detail/visibility.h++>

namespace ogonek {
    struct OGONEK_PUBLIC atari_st_codepage {
        static OGONEK_PUBLIC code_point to_unicode[256];
        static OGONEK_PUBLIC detail::simple_byte_mapping from_unicode[256];
    };

    using atari_st = detail::simple_byte_mapping_encoding<atari_st_codepage>;

    CONCEPT_ASSERT(EncodingForm<atari_st>());
} // namespace ogonek

#endif // OGONEK_ATARI_ST_HPP
