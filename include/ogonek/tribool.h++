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

#ifndef OGONEK_TRIBOOL_HPP
#define OGONEK_TRIBOOL_HPP

#ifdef OGONEK_USE_BOOST
#   include <boost/tribool.hpp>
#endif

namespace ogonek {
    struct tribool;

    struct maybe_t {
        constexpr bool operator()(tribool t) const noexcept;
    } constexpr maybe = {};

    struct tribool {
    private:
        static constexpr char maybe_value = -1;

    public:
        constexpr tribool() noexcept
        : tribool(false) {}

        constexpr tribool(bool v) noexcept
        : v(v) {}

        constexpr tribool(maybe_t) noexcept
        : v(maybe_value) {}

        constexpr explicit operator bool() const noexcept {
            return v == true;
        }

#ifdef OGONEK_USE_BOOST
        constexpr tribool(boost::tribool t) noexcept
        : v(boost::indeterminate(t)? maybe_value : t == true) {}

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

    constexpr tribool operator!(tribool t) noexcept {
        return maybe(t)? tribool(maybe) : tribool(!t.v);
    }

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

#endif // OGONEK_TRIBOOL_HPP
