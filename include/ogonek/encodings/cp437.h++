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

// CP 437 encoding form

#ifndef OGONEK_ENCODINGS_CP437_HPP
#define OGONEK_ENCODINGS_CP437_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts.h++>
#include <ogonek/detail/simple_byte_mapping_encoding.h++>

namespace ogonek {
    struct cp437_codepage {
        static code_point to_unicode[256];
        static detail::simple_byte_mapping from_unicode[256];
    };

    using cp437 = detail::simple_byte_mapping_encoding<cp437_codepage>;

    CONCEPT_ASSERT(EncodingForm<cp437>());
} // namespace ogonek

#endif // OGONEK_CP437_HPP
