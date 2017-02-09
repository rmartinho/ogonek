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

// CP 1255 encoding form

#ifndef OGONEK_ENCODINGS_CP1255_HPP
#define OGONEK_ENCODINGS_CP1255_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts.h++>
#include <ogonek/detail/simple_byte_mapping_encoding.h++>

namespace ogonek {
    struct cp1255_codepage {
        static code_point to_unicode[256];
        static detail::simple_byte_mapping from_unicode[233];
    };

    using cp1255 = detail::simple_byte_mapping_encoding<cp1255_codepage>;

    CONCEPT_ASSERT(EncodingForm<cp1255>());
} // namespace ogonek

#endif // OGONEK_CP1255_HPP
