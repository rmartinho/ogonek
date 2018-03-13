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
 * Error handling
 * ==============
 */

#ifndef OGONEK_ERROR_HPP
#define OGONEK_ERROR_HPP

#include <ogonek/error_fwd.h++>

#include <ogonek/concepts/encoding.h++>
#include <ogonek/encoding.h++>
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
            return u8"encoding failed ";
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
     * .. var:: auto assume_valid
     *
     *     A tag used to request that encoding/decoding functions assume the
     *     input has been validated before.
     *
     *     .. warning::
     *
     *         Using this tag with input that isn't actually valid yields
     *         undefined behavior.
     */
    struct assume_valid_t {} constexpr assume_valid {};

    /**
     * .. var:: auto discard_errors
     *
     *     An error handler for encoding/decoding functions that simply
     *     discards the portions of the input that have errors.
     */
    struct discard_errors_t {
        template <typename E>
        detail::optional<code_point> operator()(E) const {
            return {};
        }
    } constexpr discard_errors {};

    CONCEPT_ASSERT(EncodeErrorHandler<discard_errors_t, archetypes::EncodingForm>());
    CONCEPT_ASSERT(DecodeErrorHandler<discard_errors_t, archetypes::EncodingForm>());

    /**
     * .. var:: auto replace_errors
     *
     *     An error handler for encoding/decoding functions that replaces
     *     portions of the input that have errors with a replacement character.
     *     When decoding, this is |u-fffd|, but when encoding and the target
     *     doesn't support it, some encoding-specific character is used
     *     instead.
     */
    struct replace_errors_t {
        template <typename Encoding,
                  CONCEPT_REQUIRES_(EncodingForm<Encoding>())>
        detail::optional<code_point> operator()(encode_error<Encoding>) const {
            return replacement_character_v<Encoding>;
        }
        template <typename Encoding,
                  CONCEPT_REQUIRES_(EncodingForm<Encoding>())>
        detail::optional<code_point> operator()(decode_error<Encoding>) const {
            return { U'\uFFFD' };
        }
    } constexpr replace_errors {};

    CONCEPT_ASSERT(EncodeErrorHandler<replace_errors_t, archetypes::EncodingForm>());
    CONCEPT_ASSERT(DecodeErrorHandler<replace_errors_t, archetypes::EncodingForm>());

    /**
     * .. var:: auto throw_error
     *
     *     An error handler for encoding/decoding functions that throws when an
     *     error is found in the input.
     */
    struct throw_error_t {
        template <typename E>
        detail::optional<code_point> operator()(E e) const {
            throw e;
        }
    } constexpr throw_error {};

    CONCEPT_ASSERT(EncodeErrorHandler<throw_error_t, archetypes::EncodingForm>());
    CONCEPT_ASSERT(DecodeErrorHandler<throw_error_t, archetypes::EncodingForm>());
} // namespace ogonek

#endif // OGONEK_ERROR_HPP
