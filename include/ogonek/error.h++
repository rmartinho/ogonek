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

#include <ogonek/error_fwd.h++>

#include <ogonek/concepts.h++>
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
    struct encode_error
    : virtual unicode_error {
        char const* what() const noexcept override {
            return u8"encoding failed";
        }
    };

    /**
     * .. class:: decode_error : virtual unicode_error
     *
     *     :thrown: when an error occurs during a decoding operation.
     */
    struct decode_error
    : virtual unicode_error {
        char const* what() const noexcept override {
            return u8"decoding failed";
        }
    };

    /**
     * .. todo:: ``assume_valid``
     */
    struct {} constexpr assume_valid {};

    /**
     * .. todo:: ``discard_errors``
     */
    struct {
        detail::optional<code_point> operator()(encode_error) const {
            return {};
        }
    } constexpr discard_errors {};

    CONCEPT_ASSERT(EncodeErrorHandler<decltype(discard_errors)>());

    /**
     * .. todo:: ``replace_errors``
     */
    //struct {
    //    detail::optional<code_point> operator()(encode_error) const {
    //        return replacement_character_v<Encoding>;
    //    }
    //} constexpr replace_errors {};

    //CONCEPT_ASSERT(EncodeErrorHandler<decltype(replace_errors)>());

    /**
     * .. todo:: ``throw_error``
     */
    struct {
        detail::optional<code_point> operator()(encode_error e) const {
            throw e;
        }
    } constexpr throw_error {};

    CONCEPT_ASSERT(EncodeErrorHandler<decltype(throw_error)>());
} // namespace ogonek

#endif // OGONEK_ERROR_HPP
