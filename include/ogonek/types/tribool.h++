// Ogonek
//
// Written in 2018 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

/**
 * 3-state boolean type
 * ====================
 */

#ifndef OGONEK_TYPES_TRIBOOL_HPP
#define OGONEK_TYPES_TRIBOOL_HPP

#ifdef OGONEK_USE_BOOST
#   include <boost/tribool.hpp>
#endif

namespace ogonek {
    struct tribool;

    /**
     * .. class:: maybe_t
     *
     *     The unit type of the :var:`maybe` constant.
     */
    struct maybe_t {
#ifdef OGONEK_USE_BOOST
        constexpr maybe_t(decltype(boost::indeterminate)) noexcept {}
        constexpr operator decltype(boost::indeterminate)() const noexcept {
            return boost::indeterminate;
        }
#endif
        /**
         *     .. function:: constexpr bool operator()(tribool t) const noexcept
         *
         *         :param t: a :class:`tribool` to check for a maybe state
         *
         *         :returns: ``true`` if ``t`` is maybe; ``false`` otherwise
         *
         */
        constexpr bool operator()(tribool t) const noexcept;
    } constexpr maybe = {};
    /**
     * .. var:: constexpr maybe_t maybe
     *
     *     A constant used to represent the third boolean state.
     */

    /**
     * .. class:: tribool
     *
     *     A 3-state boolean type. The third state represents a superposition
     *     of the ``true`` and ``false`` states.
     */
    struct tribool {
    private:
        static constexpr char maybe_value = -1;

    public:
        /**
         *     .. function:: constexpr tribool() noexcept
         *
         *         Creates a new tribool, with the ``false`` value.
         */
        constexpr tribool() noexcept
        : tribool(false) {}

        /**
         *     .. function:: constexpr tribool(bool v) noexcept
         *
         *         Creates a new tribool, with the given value.
         *
         *         :param v: the value of the new tribool
         */
        constexpr tribool(bool v) noexcept
        : v(v) {}


        /**
         *     .. function:: constexpr tribool(maybe_t) noexcept
         *
         *         Creates a new tribool, with the maybe state.
         */
        constexpr tribool(maybe_t) noexcept
        : v(maybe_value) {}

        /**
         *     .. function:: constexpr explicit operator bool() const noexcept
         *
         *         :returns: ``true`` if the state is true; ``false`` otherwise.
         */
        constexpr explicit operator bool() const noexcept {
            return v == true;
        }

#ifdef OGONEK_USE_BOOST

        /**
         *     .. note:: |boost|
         *
         *         .. function:: constexpr tribool(boost::tribool t) noexcept
         *
         *             Creates a new tribool with the value of a ``boost::tribool``.
         */
        constexpr tribool(boost::tribool t) noexcept
        : v(boost::indeterminate(t)? maybe_value : t == true) {}

        /**
         *         .. function:: constexpr operator boost::tribool() const noexcept
         *
         *             :returns: a ``boost::tribool`` equivalent to this tribool.
         */
        constexpr operator boost::tribool() const noexcept {
            return v == maybe_value? boost::tribool(boost::indeterminate) : boost::tribool(v);
        }
#endif

    private:
        friend struct maybe_t;

        friend constexpr tribool operator!(tribool t) noexcept;

        friend constexpr tribool operator&&(tribool lhs, tribool rhs) noexcept;
        friend constexpr tribool operator&&(tribool lhs, bool rhs) noexcept;
        friend constexpr tribool operator&&(bool lhs, tribool rhs) noexcept;
        friend constexpr tribool operator&&(maybe_t, tribool) noexcept;
        friend constexpr tribool operator&&(tribool, maybe_t) noexcept;

        friend constexpr tribool operator||(tribool lhs, tribool rhs) noexcept;
        friend constexpr tribool operator||(tribool lhs, bool rhs) noexcept;
        friend constexpr tribool operator||(bool lhs, tribool rhs) noexcept;
        friend constexpr tribool operator||(maybe_t, tribool rhs) noexcept;
        friend constexpr tribool operator||(tribool lhs, maybe_t) noexcept;

        friend constexpr tribool operator==(tribool lhs, tribool rhs) noexcept;
        friend constexpr tribool operator==(tribool lhs, bool rhs) noexcept;
        friend constexpr tribool operator==(bool lhs, tribool rhs) noexcept;
        friend constexpr tribool operator==(maybe_t, tribool rhs) noexcept;
        friend constexpr tribool operator==(tribool lhs, maybe_t) noexcept;

        friend constexpr tribool operator!=(tribool lhs, tribool rhs) noexcept;
        friend constexpr tribool operator!=(tribool lhs, bool rhs) noexcept;
        friend constexpr tribool operator!=(bool lhs, tribool rhs) noexcept;
        friend constexpr tribool operator!=(maybe_t, tribool rhs) noexcept;
        friend constexpr tribool operator!=(tribool lhs, maybe_t) noexcept;

        char v;
    };

    constexpr bool maybe_t::operator()(tribool t) const noexcept {
        return t.v == tribool::maybe_value;
    }

    /**
     * .. function:: constexpr tribool operator!(tribool t) noexcept
     *
     *     Negates a tribool.
     *
     *     :returns: :var:`maybe` if `t` is :var:`maybe`; otherwise ``!bool(t)``
     */
    constexpr tribool operator!(tribool t) noexcept {
        return maybe(t)? tribool(maybe) : tribool(!t.v);
    }

    /**
     * .. function:: constexpr tribool operator&&(tribool lhs, tribool rhs) noexcept
     * .. function:: constexpr tribool operator&&(tribool lhs, bool rhs) noexcept
     * .. function:: constexpr tribool operator&&(bool lhs, tribool rhs) noexcept
     * .. function:: constexpr tribool operator&&(maybe_t lhs, tribool rhs) noexcept
     * .. function:: constexpr tribool operator&&(tribool lhs, maybe_t rhs) noexcept
     *
     *     Logical conjunction of tribools.
     *
     *     :returns: :var:`maybe` if either side is :var:`maybe`; otherwise
     *               ``bool(lhs) && bool(rhs)``
     */
    constexpr tribool operator&&(tribool lhs, tribool rhs) noexcept {
        return maybe(lhs) || maybe(rhs)? tribool(maybe) : tribool(lhs.v && rhs.v);
    }
    constexpr tribool operator&&(tribool lhs, bool rhs) noexcept {
        return maybe(lhs)? tribool(maybe) : tribool(lhs.v && rhs);
    }
    constexpr tribool operator&&(bool lhs, tribool rhs) noexcept {
        return maybe(rhs)? tribool(maybe) : tribool(lhs && rhs.v);
    }
    constexpr tribool operator&&(maybe_t, tribool) noexcept {
        return maybe;
    }
    constexpr tribool operator&&(tribool, maybe_t) noexcept {
        return maybe;
    }

    /**
     * .. function:: constexpr tribool operator||(tribool lhs, tribool rhs) noexcept
     * .. function:: constexpr tribool operator||(tribool lhs, bool rhs) noexcept
     * .. function:: constexpr tribool operator||(bool lhs, tribool rhs) noexcept
     * .. function:: constexpr tribool operator||(maybe_t lhs, tribool rhs) noexcept
     * .. function:: constexpr tribool operator||(tribool lhs, maybe_t rhs) noexcept
     *
     *     Logical disjunction of tribools.
     *
     *     :returns: ``true`` if either side is ``true``; otherwise :var:`maybe`
     *               if either side is :var:`maybe`; otherwise ``false``
     */
    constexpr tribool operator||(tribool lhs, tribool rhs) noexcept {
        return lhs? true : rhs? true : maybe(lhs) || maybe(rhs)? tribool(maybe) : false;
    }
    constexpr tribool operator||(tribool lhs, bool rhs) noexcept {
        return lhs? true : rhs? true : maybe(lhs)? tribool(maybe) : false;
    }
    constexpr tribool operator||(bool lhs, tribool rhs) noexcept {
        return lhs? true : rhs? true : maybe(rhs)? tribool(maybe) : false;
    }
    constexpr tribool operator||(maybe_t, tribool rhs) noexcept {
        return rhs? true : tribool(maybe);
    }
    constexpr tribool operator||(tribool lhs, maybe_t) noexcept {
        return lhs? true : tribool(maybe);
    }

    /**
     * .. function:: constexpr tribool operator==(tribool lhs, tribool rhs) noexcept
     * .. function:: constexpr tribool operator==(tribool lhs, bool rhs) noexcept
     * .. function:: constexpr tribool operator==(bool lhs, tribool rhs) noexcept
     * .. function:: constexpr tribool operator==(maybe_t lhs, tribool rhs) noexcept
     * .. function:: constexpr tribool operator==(tribool lhs, maybe_t rhs) noexcept
     *
     *     Compares tribools for equality.
     *
     *     :returns: :var:`maybe` if either side is :var:`maybe`; otherwise
     *               ``bool(lhs) == bool(rhs)``
     */
    constexpr tribool operator==(tribool lhs, tribool rhs) noexcept {
        return maybe(lhs) || maybe(rhs)? tribool(maybe) : tribool(lhs.v == rhs.v);
    }
    constexpr tribool operator==(tribool lhs, bool rhs) noexcept {
        return maybe(lhs)? tribool(maybe) : tribool(lhs.v == rhs);
    }
    constexpr tribool operator==(bool lhs, tribool rhs) noexcept {
        return maybe(rhs)? tribool(maybe) : tribool(lhs == rhs.v);
    }
    constexpr tribool operator==(maybe_t, tribool) noexcept {
        return maybe;
    }
    constexpr tribool operator==(tribool, maybe_t) noexcept {
        return maybe;
    }

    /**
     * .. function:: constexpr tribool operator!=(tribool lhs, tribool rhs) noexcept
     * .. function:: constexpr tribool operator!=(tribool lhs, bool rhs) noexcept
     * .. function:: constexpr tribool operator!=(bool lhs, tribool rhs) noexcept
     * .. function:: constexpr tribool operator!=(maybe_t lhs, tribool rhs) noexcept
     * .. function:: constexpr tribool operator!=(tribool lhs, maybe_t rhs) noexcept
     *
     *     Compares tribools for inequality.
     *
     *     :returns: :var:`maybe` if either side is :var:`maybe`; otherwise
     *               ``bool(lhs) != bool(rhs)``
     */
    constexpr tribool operator!=(tribool lhs, tribool rhs) noexcept {
        return maybe(lhs) || maybe(rhs)? tribool(maybe) : tribool(lhs.v != rhs.v);
    }
    constexpr tribool operator!=(tribool lhs, bool rhs) noexcept {
        return maybe(lhs)? tribool(maybe) : tribool(lhs.v != rhs);
    }
    constexpr tribool operator!=(bool lhs, tribool rhs) noexcept {
        return maybe(rhs)? tribool(maybe) : tribool(lhs != rhs.v);
    }
    constexpr tribool operator!=(maybe_t, tribool) noexcept {
        return maybe;
    }
    constexpr tribool operator!=(tribool, maybe_t) noexcept {
        return maybe;
    }
} // namespace ogonek

#endif // OGONEK_TYPES_TRIBOOL_HPP
