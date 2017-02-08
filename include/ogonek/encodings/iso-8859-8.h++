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

// ISO-8859-8 encoding form

#ifndef OGONEK_ENCODINGS_ISO_8859_8_HPP
#define OGONEK_ENCODINGS_ISO_8859_8_HPP

#include <ogonek/types.h++>
#include <ogonek/detail/simple_byte_mapping_encoding.h++>

namespace ogonek {
    struct iso_8859_8_codepage {
        static code_point to_unicode[256];
        static detail::simple_byte_mapping from_unicode[220];
    };

    using iso_8859_8 = detail::simple_byte_mapping_encoding<iso_8859_8_codepage>;
} // namespace ogonek

#endif // OGONEK_ISO_8859_8_HPP