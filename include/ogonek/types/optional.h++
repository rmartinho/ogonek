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

/**
 * Optional type
 * =============
 */

#ifndef OGONEK_TYPES_OPTIONAL_HPP
#define OGONEK_TYPES_OPTIONAL_HPP

#include <ogonek/concepts.h++>
#include <ogonek/types/core.h++>

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
    } // namespace detail

    /**
     * .. class:: none_t
     *
     *     The unit type of the :var:`none` constant.
     *
     * .. var:: constexpr none_t none
     *
     *     A constant used to create empty optional objects.
     *
     */
    struct none_t {
#ifdef OGONEK_HAS_STD_OPTIONAL
        constexpr none_t(decltype(detail::std_nullopt)) noexcept {}
        constexpr operator decltype(detail::std_nullopt)() const noexcept {
            return std_nullopt;
        }
#endif

#ifdef OGONEK_USE_BOOST
        constexpr none_t(decltype(boost::none)) noexcept {}
        constexpr operator decltype(boost::none)() const noexcept {
            return boost::none;
        }
#endif
    } constexpr none = {};

    /**
     * .. class:: template <typename T>\
     *            optional
     *
     *     An optional object that may or may not contain a value.
     */
    template <typename T>
    struct optional;
    /**
     *     .. function:: constexpr optional() noexcept
     *
     *         Creates a new empty optional object.
     */
    /**
     *     .. function:: constexpr optional(none_t) noexcept
     *
     *         Creates a new empty optional object.
     */
    /**
     *     .. function:: constexpr optional(T t) noexcept
     *
     *         Creates a new optional object.
     *
     *         :param t: the value of the new optional object
     */
    /**
     *     .. function:: constexpr T operator*() const noexcept
     *
     *         :requires: this optional isn't empty.
     *
     *         :returns: the value of this optional.
     */
    /**
     *     .. function:: constexpr explicit operator bool() const noexcept
     *
     *         :returns: ``true`` if this optional has a value; ``false`` if it's empty.
     */
    /**
     *     .. note:: |std17|
     *
     *         .. function:: constexpr optional(std::optional<T> o) noexcept
     *
     *             Creates a new optional from a ``std::optional``.
     *
     *             :param o: the source
     *
     *             :returns: an optional with the same value as ``o``
     */
    /**
     *         .. function:: constexpr operator std::optional<T>() const noexcept
     *
     *             Converts an optional to ``std::optional``.
     *
     *             :returns: a ``std::optional`` with the same value as this optional
     */
    /**
     *     .. note:: |boost|
     *
     *         .. function:: constexpr optional(boost::optional<T> o) noexcept
     *
     *             Creates a new optional from a ``boost::optional``.
     *
     *             :param o: the source
     *
     *             :returns: an optional with the same value as ``o``
     */
    /**
     *         .. function:: constexpr operator boost::optional<T>() const noexcept
     *
     *             Converts an optional to ``boost::optional``.
     *
     *             :returns: a ``boost::optional`` with the same value as this optional
     */

    /**
     * .. function:: template <typename T, typename U>\
     *               constexpr bool operator==(optional<T> const& lhs, optional<U> const& rhs) noexcept
     * .. function:: template <typename T>\
     *               constexpr bool operator==(optional<T> const& lhs, T const& rhs) noexcept
     * .. function:: template <typename T>\
     *               constexpr bool operator==(T const& lhs, optional<T> const& rhs) noexcept
     * .. function:: template <typename T>\
     *               constexpr bool operator==(optional<T> const& lhs, none_t) noexcept
     * .. function:: template <typename T>\
     *               constexpr bool operator==(none_t, optional<T> const& rhs) noexcept
     *
     *     Compares optional for equality.
     *
     *     :returns: ``true`` if both sides have the same value, or if neither
     *               side has a value; ``false`` otherwise.
     */
    template <typename T, typename U>
    constexpr bool operator==(optional<T> const& lhs, optional<U> const& rhs) noexcept {
        return (!lhs && !rhs) || (lhs && rhs && *lhs == *rhs);
    }
    template <typename T>
    constexpr bool operator==(optional<T> const& lhs, T const& rhs) noexcept {
        return lhs && *lhs == rhs;
    }
    template <typename T>
    constexpr bool operator==(T const& lhs, optional<T> const& rhs) noexcept {
        return rhs == lhs;
    }
    template <typename T>
    constexpr bool operator==(optional<T> const& lhs, none_t) noexcept {
        return !lhs;
    }
    template <typename T>
    constexpr bool operator==(none_t, optional<T> const& rhs) noexcept {
        return !rhs;
    }

    /**
     * .. function:: template <typename T, typename U>\
     *               constexpr bool operator!=(optional<T> const& lhs, optional<U> const& rhs) noexcept
     * .. function:: template <typename T>\
     *               constexpr bool operator!=(optional<T> const& lhs, T const& rhs) noexcept
     * .. function:: template <typename T>\
     *               constexpr bool operator!=(T const& lhs, optional<T> const& rhs) noexcept
     * .. function:: template <typename T>\
     *               constexpr bool operator!=(optional<T> const& lhs, none_t) noexcept
     * .. function:: template <typename T>\
     *               constexpr bool operator!=(none_t, optional<T> const& rhs) noexcept
     *
     *     Compares optional for inequality.
     *
     *     :returns: ``!(lhs == rhs)``
     */
    template <typename T, typename U>
    constexpr bool operator!=(optional<T> const& lhs, optional<U> const& rhs) noexcept {
        return !(lhs == rhs);
    }
    template <typename T>
    constexpr bool operator!=(optional<T> const& lhs, T const& rhs) noexcept {
        return !(lhs == rhs);
    }
    template <typename T>
    constexpr bool operator!=(T const& lhs, optional<T> const& rhs) noexcept {
        return !(lhs == rhs);
    }
    template <typename T>
    constexpr bool operator!=(optional<T> const& lhs, none_t) noexcept {
        return !(lhs == none);
    }
    template <typename T>
    constexpr bool operator!=(none_t, optional<T> const& rhs) noexcept {
        return !(none == rhs);
    }

    // trivial specializations that uses unused representation bits for nullopt
    template <>
    struct optional<code_point> {
    private:
        static constexpr code_point invalid = 0xFFFFFFFF;

    public:
        constexpr optional() noexcept
        : u(invalid) {}

        constexpr optional(none_t) noexcept
        : optional() {}

        constexpr optional(code_point u) noexcept
        : u(u) {
            assert(u != invalid);
        }

        constexpr code_point operator*() const noexcept {
            assert(u != invalid);
            return u;
        }

        constexpr explicit operator bool() const noexcept {
            return u != invalid;
        }

#ifdef OGONEK_HAS_STD_OPTIONAL
        constexpr optional(detail::std_optional<code_point> const& o) noexcept
        : u(o.value_or(invalid)) {}

        constexpr operator detail::std_optional<code_point>() const noexcept {
            return u != invalid? detail::std_optional<code_point>(u) : detail::std_nullopt;
        }
#endif

#ifdef OGONEK_USE_BOOST
        optional(boost::optional<code_point> const& o) noexcept
        : u(o.value_or(invalid)) {}

        operator boost::optional<code_point>() const noexcept {
            return boost::make_optional(u != invalid, u);
        }
#endif
    private:
        code_point u;
    };

    CONCEPT_ASSERT(Optional<optional<code_point>>());
} // namespace ogonek

#endif //OGONEK_TYPES_OPTIONAL_HPP
