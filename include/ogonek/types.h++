// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

/**
 * Core types ``<ogonek/types.h++>``
 * =================================
 */

#ifndef OGONEK_TYPES_HPP
#define OGONEK_TYPES_HPP

#include <cstdint>

namespace ogonek {

    /**
     * .. type:: code_point = char32_t
     *
     * Many algorithms in ogonek operate on sequences of code points. The
     * sequences themselves can have any type, but their elements must be code
     * points. ``code_point`` is the type used to represent code points. It is
     * an alias for the standard C++ ``char32_t`` type.
     *
     * All ``code_point`` arguments in Ogonek are required to be valid, i.e.
     * |valid-code-point|; otherwise the behaviour is undefined. The results of
     * Ogonek functions never include ``code_point`` values outside this range.
     */
    using code_point = char32_t;

    /**
     * .. type:: byte = std::uint8_t
     *
     * Encoding schemes and some encoding forms take input or produce output in
     * the form of bytes or sequences of bytes. The type used to represent
     * bytes in ogonek is called ``byte``, an alias for the standard C++
     * ``uint8_t`` type.
     */
    using byte = std::uint8_t;

    namespace detail {
        struct fraction { long num, den; };
        struct trinary { int value; };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_TYPES_HPP
