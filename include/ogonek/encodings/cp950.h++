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

// CP 950 encoding form

#ifndef OGONEK_ENCODINGS_CP950_HPP
#define OGONEK_ENCODINGS_CP950_HPP

#include <ogonek/types.h++>
#include <ogonek/detail/simple_byte_mapping_encoding.h++>

namespace ogonek {
    struct cp950_codepage {
        static code_point to_unicode[256];
        static detail::simple_byte_mapping from_unicode[13631];
    };

    using cp950 = detail::simple_byte_mapping_encoding<cp950_codepage>;
} // namespace ogonek

#endif // OGONEK_CP950_HPP