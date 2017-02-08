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

// KOI8-U encoding form

#ifndef OGONEK_ENCODINGS_KOI8_U_HPP
#define OGONEK_ENCODINGS_KOI8_U_HPP

#include <ogonek/types.h++>
#include <ogonek/detail/simple_byte_mapping_encoding.h++>

namespace ogonek {
    struct koi8_u_codepage {
        static code_point to_unicode[256];
        static detail::simple_byte_mapping from_unicode[256];
    };

    using koi8_u = detail::simple_byte_mapping_encoding<koi8_u_codepage>;
} // namespace ogonek

#endif // OGONEK_KOI8_U_HPP
