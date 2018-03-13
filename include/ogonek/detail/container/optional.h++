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

#include <ogonek/concepts.h++>
#include <ogonek/types.h++>

#ifdef OGONEK_USE_BOOST
#   include <boost/optional.hpp>
#endif

#ifdef __has_include
#   if __cplusplus >= 201703L && __has_include(<optional>)
#       include <optional>
#       define OGONEK_HAS_STD_OPTIONAL
#   elif !defined(_LIBCPP_VERSION) && __has_include(<experimental/optional>)
#       include <experimental/optional>
#       define OGONEK_HAS_STD_OPTIONAL
#       define OGONEK_HAS_STD_EXPERIMENTAL_OPTIONAL
#   endif
#endif

#include <cassert>

namespace ogonek {
    namespace detail {
#if defined(OGONEK_HAS_STD_EXPERIMENTAL_OPTIONAL)
        template <typename T>
        using std_optional = std::experimental::optional<T>;
        constexpr auto std_nullopt = std::experimental::nullopt;
#elif defined(OGONEK_HAS_STD_OPTIONAL)
        template <typename T>
        using std_optional = std::optional<T>;
        constexpr auto std_nullopt = std::nullopt;
#endif

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

#ifdef OGONEK_HAS_STD_OPTIONAL
            constexpr optional(std_optional<code_point> const& o)
            : u(o.value_or(invalid)) {}

            constexpr operator std_optional<code_point>() const {
                return u != invalid? std_optional<code_point>(u) : std_nullopt;
            }
#endif

#ifdef OGONEK_USE_BOOST
            optional(boost::optional<code_point> const& o)
            : u(o.value_or(invalid)) {}

            operator boost::optional<code_point>() const {
                return boost::make_optional(u != invalid, u);
            }
#endif
        private:
            code_point u;
        };

        CONCEPT_ASSERT(Optional<optional<code_point>>());
    } // namespace detail
} // namespace ogonek

#endif //OGONEK_DETAIL_CONTAINER_OPTIONAL_HPP
