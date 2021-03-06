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

// Mac OS Romanian encoding form

#ifndef OGONEK_ENCODINGS_MAC_ROMANIAN_HPP
#define OGONEK_ENCODINGS_MAC_ROMANIAN_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts.h++>
#include <ogonek/detail/encoding/simple_byte_mapping_encoding.h++>
#include <ogonek/detail/visibility.h++>

namespace ogonek {
    struct OGONEK_PUBLIC mac_romanian_codepage {
        static OGONEK_PUBLIC code_point to_unicode[256];
        static OGONEK_PUBLIC detail::simple_byte_mapping from_unicode[223];
    };

    using mac_romanian = detail::simple_byte_mapping_encoding<mac_romanian_codepage>;

    CONCEPT_ASSERT(EncodingForm<mac_romanian>());
} // namespace ogonek

#endif // OGONEK_MAC_ROMANIAN_HPP
