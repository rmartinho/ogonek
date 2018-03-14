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

#ifndef OGONEK_TYPES_FRACTION_HPP
#define OGONEK_TYPES_FRACTION_HPP

#include <ogonek/concepts.h++>
#include <ogonek/types/optional.h++>

#ifdef OGONEK_USE_BOOST
#   include <boost/rational.hpp>
#endif

#include <cassert>

namespace ogonek {
    struct fraction {
    public:
        constexpr fraction() noexcept
        : fraction(0, 1) {}

        constexpr fraction(long numerator, long denominator) noexcept
        : num(numerator), den(denominator) {
            assert(denominator != 0);
        }

        constexpr long numerator() const noexcept {
            return num;
        }

        constexpr long denominator() const noexcept {
            return den;
        }

        constexpr double as_double() const noexcept {
            return static_cast<double>(num) / den;
        }

#ifdef OGONEK_USE_BOOST
        constexpr fraction(boost::rational<long> r) noexcept
        : num(r.numerator()), den(r.denominator()) {}

        constexpr operator boost::rational<long>() const noexcept {
            return boost::rational<long>(num, den);
        }
#endif

    private:
        friend struct optional<fraction>;

        long num;
        long den;
    };

    constexpr bool operator==(fraction lhs, fraction rhs) noexcept {
        return lhs.numerator() == rhs.numerator()
            && lhs.denominator() == rhs.denominator();
    }
    constexpr bool operator!=(fraction lhs, fraction rhs) noexcept {
        return !(lhs == rhs);
    }

    // trivial specializations that uses unused representation bits for nullopt
    template <>
    struct optional<fraction> {
    private:
        static constexpr fraction invalid() noexcept {
            fraction f;
            f.den = 0;
            return f;
        }

    public:
        constexpr optional() noexcept
        : f(invalid()) {}

        constexpr optional(none_t)
        : optional() {}

        constexpr optional(fraction f) noexcept
        : f(f) {
            assert(f.den != 0);
        }

        constexpr fraction operator*() const noexcept {
            assert(f.den != 0);
            return f;
        }

        explicit constexpr operator bool() const noexcept {
            return f.den != 0;
        }

#ifdef OGONEK_HAS_STD_OPTIONAL
        constexpr optional(std_optional<fraction> const& o) noexcept
        : f(o.value_or(invalid())) {}

        constexpr operator std_optional<fraction>() const noexcept {
            return f.den != 0? std_optional<fraction>(f) : std_nullopt;
        }
#endif

#ifdef OGONEK_USE_BOOST
        optional(boost::optional<fraction> const& o) noexcept
        : u(o.value_or(invalid())) {}

        operator boost::optional<fraction>() const noexcept {
            return boost::make_optional(f.den != 0, f);
        }
#endif
    private:
        fraction f;
    };

    CONCEPT_ASSERT(Optional<optional<fraction>>());
} // namespace ogonek

#endif // OGONEK_TYPES_FRACTION_HPP
