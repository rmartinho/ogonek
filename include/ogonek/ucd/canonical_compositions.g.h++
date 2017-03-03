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

// Unicode character database - $Canonical_Compositions property

#ifndef OGONEK_UCD_CANONICAL_COMPOSITIONS_HPP
#define OGONEK_UCD_CANONICAL_COMPOSITIONS_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>
#include <initializer_list>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
    struct composition_entry {
        code_point with;
        code_point result;
    };
            struct canonical_compositions_properties {
                code_point start;
                std::initializer_list<composition_entry> value;
            };

            extern OGONEK_PUBLIC canonical_compositions_properties const* canonical_compositions_data;
            extern OGONEK_PUBLIC std::size_t canonical_compositions_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_CANONICAL_COMPOSITIONS_HPP
