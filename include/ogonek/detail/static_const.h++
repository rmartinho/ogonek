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

// Static constants

#ifndef OGONEK_DETAIL_STATIC_CONST_HPP
#define OGONEK_DETAIL_STATIC_CONST_HPP

namespace ogonek {
    namespace detail {
        template <typename T>
        struct static_const {
            static constexpr T value {};
        };
        template <typename T>
        constexpr T static_const<T>::value;
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_STATIC_CONST_HPP
