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

// CP 1254 encoding form

#ifndef OGONEK_ENCODINGS_CP1254_HPP
#define OGONEK_ENCODINGS_CP1254_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts.h++>
#include <ogonek/detail/simple_byte_mapping_encoding.h++>
#include <ogonek/detail/visibility.h++>

namespace ogonek {
    struct OGONEK_PUBLIC cp1254_codepage {
        static OGONEK_PUBLIC code_point to_unicode[256];
        static OGONEK_PUBLIC detail::simple_byte_mapping from_unicode[249];
    };

    using cp1254 = detail::simple_byte_mapping_encoding<cp1254_codepage>;

    CONCEPT_ASSERT(EncodingForm<cp1254>());
} // namespace ogonek

#endif // OGONEK_CP1254_HPP
