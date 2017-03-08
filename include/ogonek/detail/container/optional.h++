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

// Simple internal optional<T> implementation for our own types

#ifndef OGONEK_DETAIL_CONTAINER_OPTIONAL_HPP
#define OGONEK_DETAIL_CONTAINER_OPTIONAL_HPP

#include <ogonek/concepts/core.h++>
#include <ogonek/types.h++>

#include <cassert>

namespace ogonek {
    namespace detail {
        template <typename T>
        struct optional;

        // trivial specializations that uses unused representation bits for nullopt
        template <>
        struct optional<code_point> {
        private:
            static constexpr code_point invalid = 0xFFFFFFFF;

        public:
            constexpr optional()
            : u(invalid) {}

            constexpr optional(code_point u)
            : u(u) {
                assert(u != invalid);
            }

            constexpr code_point operator*() const {
                assert(u != invalid);
                return u;
            }

            explicit constexpr operator bool() const {
                return u != invalid;
            }

        private:
            code_point u;
        };

        CONCEPT_ASSERT(Optional<optional<code_point>>());
    } // namespace detail
} // namespace ogonek

#endif //OGONEK_DETAIL_CONTAINER_OPTIONAL_HPP
