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

// CP 865 encoding form

#ifndef OGONEK_ENCODINGS_CP865_HPP
#define OGONEK_ENCODINGS_CP865_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts.h++>
#include <ogonek/detail/simple_byte_mapping_encoding.h++>
#include <ogonek/detail/visibility.h++>

namespace ogonek {
    struct OGONEK_PUBLIC cp865_codepage {
        static OGONEK_PUBLIC code_point to_unicode[256];
        static OGONEK_PUBLIC detail::simple_byte_mapping from_unicode[256];
    };

    using cp865 = detail::simple_byte_mapping_encoding<cp865_codepage>;

    CONCEPT_ASSERT(EncodingForm<cp865>());
} // namespace ogonek

#endif // OGONEK_CP865_HPP
