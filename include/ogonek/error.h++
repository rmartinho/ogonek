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
     * .. class:: template <EncodingForm Encoding>\
     *            encode_error : virtual unicode_error
     *
     *     :thrown: when an error occurs during an encoding operation.
     */
    template <typename Encoding>
    struct encode_error
    : virtual unicode_error {
        CONCEPT_ASSERT(EncodingForm<Encoding>());

        char const* what() const noexcept override {
            return u8"encoding failed";
        }
    };

    /**
     * .. class:: template <EncodingForm Encoding>\
     *            decode_error : virtual unicode_error
     *
     *     :thrown: when an error occurs during a decoding operation.
     */
    template <typename Encoding>
    struct decode_error
    : virtual unicode_error {
        CONCEPT_ASSERT(EncodingForm<Encoding>());

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
        template <typename Encoding,
                  CONCEPT_REQUIRES_(EncodingForm<Encoding>())>
        detail::optional<code_point> operator()(encode_error<Encoding>) const {
            return {};
        }
    } constexpr discard_errors {};

    CONCEPT_ASSERT(EncodeErrorHandler<decltype(discard_errors), archetypes::EncodingForm>());

    /**
     * .. todo:: ``replace_errors``
     */
    struct {
        template <typename Encoding,
                  CONCEPT_REQUIRES_(EncodingForm<Encoding>())>
        detail::optional<code_point> operator()(encode_error<Encoding>) const {
            return replacement_character_v<Encoding>;
        }
    } constexpr replace_errors {};

    CONCEPT_ASSERT(EncodeErrorHandler<decltype(replace_errors), archetypes::EncodingForm>());

    /**
     * .. todo:: ``throw_error``
     */
    struct {
        template <typename Encoding,
                  CONCEPT_REQUIRES_(EncodingForm<Encoding>())>
        detail::optional<code_point> operator()(encode_error<Encoding> e) const {
            throw e;
        }
    } constexpr throw_error {};

    CONCEPT_ASSERT(EncodeErrorHandler<decltype(throw_error), archetypes::EncodingForm>());
} // namespace ogonek

#endif // OGONEK_ERROR_HPP
