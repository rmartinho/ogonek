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
 * Error ``<ogonek/error.h++>``
 * =============================================
 */

#ifndef OGONEK_ERROR_HPP
#define OGONEK_ERROR_HPP

#include <ogonek/concepts.h++>
#include <ogonek/detail/encoded_character.h++>
#include <ogonek/detail/container/optional.h++>

#include <range/v3/range_concepts.hpp>
#include <range/v3/range_traits.hpp>

#include <stdexcept>

namespace ogonek {

    /**
     * .. class:: unicode_error
     *
     *     The base class for all Unicode-related errors.
     */
    struct unicode_error
    : virtual std::exception {
        char const* what() const noexcept override {
            return u8"Unicode error";
        }
    };

    /**
     * .. class:: encode_error : virtual unicode_error
     *
     *     :thrown: when an error occurs during an encoding operation.
     */
    template <typename Encoding, typename Rng>
    struct encode_error
    : virtual unicode_error {
    public:
        encode_error(ranges::range_iterator_t<Rng> it, ranges::range_sentinel_t<Rng> st)
        : it(std::move(it)), st(std::move(st)) {}

        char const* what() const noexcept override {
            return u8"encoding failed";
        }

        ranges::range_iterator_t<Rng> it;
        ranges::range_sentinel_t<Rng> st;
    };

    /**
     * .. class:: decode_error : virtual unicode_error
     *
     *     :thrown: when an error occurs during a decoding operation.
     */
    template <typename Encoding, typename Rng>
    struct decode_error
    : virtual unicode_error {
    public:
        decode_error(ranges::range_iterator_t<Rng> it, ranges::range_sentinel_t<Rng> st)
        : it(std::move(it)), st(std::move(st)) {}

        char const* what() const noexcept override {
            return u8"decoding failed";
        }

        ranges::range_iterator_t<Rng> it;
        ranges::range_sentinel_t<Rng> st;
    };

    template <typename Encoding>
    struct encode_error_handler_result {
        detail::optional<encoded_character<Encoding>> character;

        template <typename T> // TODO constrain?
        explicit operator T() const {
            return T(character.begin(), character.end());
        }
    };
} // namespace ogonek

#endif // OGONEK_ERROR_HPP
