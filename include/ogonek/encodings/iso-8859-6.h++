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

// ISO-8859-6 encoding form

#ifndef OGONEK_ENCODINGS_ISO_8859_6_HPP
#define OGONEK_ENCODINGS_ISO_8859_6_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts.h++>
#include <ogonek/detail/encoding/simple_byte_mapping_encoding.h++>
#include <ogonek/detail/visibility.h++>

namespace ogonek {
    struct OGONEK_PUBLIC iso_8859_6_codepage {
        static OGONEK_PUBLIC code_point to_unicode[256];
        static OGONEK_PUBLIC detail::simple_byte_mapping from_unicode[211];
    };

    using iso_8859_6 = detail::simple_byte_mapping_encoding<iso_8859_6_codepage>;

    CONCEPT_ASSERT(EncodingForm<iso_8859_6>());
} // namespace ogonek

#endif // OGONEK_ISO_8859_6_HPP
