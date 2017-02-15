// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

/**
 * Encoding ``<ogonek/encoding.h++>``
 * ==================================
 */

#ifndef OGONEK_ENCODING_HPP
#define OGONEK_ENCODING_HPP

#include <ogonek/types.h++>
#include <ogonek/error_fwd.h++>
#include <ogonek/concepts.h++>
#include <ogonek/detail/container/partial_array.h++>

#include <range/v3/view_adaptor.hpp>
#include <range/v3/view_facade.hpp>

#include <functional>
#include <iostream>
#include <type_traits>

#include <cstddef>

namespace ogonek {

    /**
     * .. type:: template <EncodingForm Encoding>\
     *           code_unit_t
     * 
     *     The type of the |code-units| used by ``Encoding``.
     */
    template <typename Encoding>
    using code_unit_t = typename concepts::EncodingForm::code_unit_t<Encoding>;

    /**
     * .. todo:: ``max_width_v``
     */
    template <typename Encoding>
    constexpr auto max_width_v = concepts::EncodingForm::max_width_v<Encoding>;

    /**
     * .. todo:: ``replacement_character_v``
     */
    template <typename Encoding>
    constexpr auto replacement_character_v = concepts::EncodingForm::replacement_character_v<Encoding>;

    /**
     * .. type:: template <EncodingForm Encoding>\
     *           encoding_state_t
     * 
     *     The type of the state used by ``Encoding``. For stateless encoding forms
     *     this is an empty type.
     */
    template <typename Encoding>
    using encoding_state_t = typename concepts::EncodingForm::state_t<Encoding>;

    /**
     * .. type:: template <EncodingForm Encoding>\
     *           is_stateless
     * 
     *     Derives from ``std::true_type`` if ``Encoding`` is stateless; from
     *     ``std::false_type`` otherwise.
     */
    template <typename Encoding>
    using is_stateless = std::is_empty<encoding_state_t<Encoding>>;

    /**
     * .. var:: template <EncodingForm Encoding>\
     *          constexpr bool is_stateless_v
     * 
     *     True if ``Encoding`` is stateless; false otherwise.
     */
    template <typename Encoding>
    constexpr bool is_stateless_v = is_stateless<Encoding>::value;

    /**
     * .. function:: template <EncodingForm Encoding>\
     *               auto encode_one(code_point u, encoding_state_t<Encoding>& state)
     *
     *     Encodes ``u`` according to ``Encoding``.
     *
     *     :param u: the |code-point| to be encoded
     *
     *     :param state: the current encoding state; it is modified according to the encoding performed
     *
     *     :returns: a range of the |code-units| that encode ``u``
     *
     *     :validation: as performed by ``Encoding``
     */
    template <typename Encoding>
    auto encode_one(code_point u, encoding_state_t<Encoding>& state) {
        return concepts::EncodingForm::encode_one<Encoding>(u, state);
    }

    namespace detail {
        template <typename Encoding, typename Rng, typename Handler>
        struct encoded_view
        : ranges::view_adaptor<
            encoded_view<Encoding, Rng, Handler>,
            Rng,
            ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value> {
        private:
            using base_type = ranges::view_adaptor<
                encoded_view<Encoding, Rng, Handler>,
                Rng,
                ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value>;

            CONCEPT_ASSERT(InputRangeOf<code_point, Rng>());
            CONCEPT_ASSERT(EncodingForm<Encoding>());
            CONCEPT_ASSERT(EncodeErrorHandler<Handler>());

            friend ranges::range_access;

            struct adaptor : public ranges::adaptor_base {
            public:
                typename Encoding::code_unit read(ranges::range_iterator_t<Rng> it) const {
                    if(position == invalid) {
                        encoded = encode_one<Encoding>(*it, state);
                        position = 0;
                    }
                    return encoded[position];
                }

                void next(ranges::range_iterator_t<Rng>& it) {
                    // TODO next without get!
                    ++position;
                    if(position == static_cast<ptrdiff_t>(encoded.size())) {
                        ++it;
                        position = invalid;
                    }
                }

                bool equal(ranges::range_iterator_t<Rng> it0, ranges::range_iterator_t<Rng> it1, adaptor const & other) const {
                    return it0 == it1 && position == other.position;
                }

                adaptor() = default;

                adaptor(Handler const& handler)
                : handler(&handler) {}

            private:
                static constexpr std::ptrdiff_t invalid = -1;

                // TODO promote this?
                using encoded_character_type = decltype(encode_one<Encoding>(code_point(), std::declval<encoding_state_t<Encoding>&>()));
                mutable encoded_character_type encoded;
                mutable std::ptrdiff_t position = invalid;
                std::decay_t<Handler> const* handler = nullptr;
                mutable encoding_state_t<Encoding> state {};
            };

            adaptor begin_adaptor() const {
                return { handler };
            }

        public:
            encoded_view() = default;
            explicit encoded_view(Rng rng, Handler handler)
            : base_type(std::move(rng)), handler(std::forward<Handler>(handler))
            {}

        private:
            std::decay_t<Handler> handler;
        };
    } // namespace detail

    /**
     * .. function:: template <EncodingForm Encoding, InputRange Rng, ErrorHandler Handler>\
     *               auto encode(Rng rng, Handler handler)
     *
     *     :param rng: The range of |code-points| to encode
     *
     *     :param handler: The strategy for error handling
     *
     *     :returns: a range of the |code-units| that encode the |code-points| in ``rng``
     *
     *     :validation: as performed by ``Encoding``; errors are handled by ``handler``
     */
    template <typename Encoding, typename Rng, typename Handler,
              CONCEPT_REQUIRES_(InputRangeOf<code_point, Rng>()),
              CONCEPT_REQUIRES_(EncodingForm<Encoding>()),
              CONCEPT_REQUIRES_(EncodeErrorHandler<Handler>())>
    auto encode(Rng rng, Handler&& handler) {
        return detail::encoded_view<Encoding, Rng, Handler>(std::move(rng), std::forward<Handler>(handler));
    }

    /**
     * .. function:: template <EncodingForm Encoding, Iterator It, Sentinel St>\
     *               std::pair<code_point, It> decode_one(It first, St last, encoding_state_t<Encoding>& state)
     *
     *     Decodes the first |code-point| from the range [``first``, ``last``), according to ``Encoding``.
     *
     *     :param first: an iterator to the first |code-unit| to be decoded
     *
     *     :param last: an iterator/sentinel to the end of the range of |code-units|
     *
     *     :param state: the current decoding state; it is modified according to the decoding performed
     *
     *     :returns: a pair of the decoded |code-point| and an iterator to first |code-unit| of the next encoded |code-point|
     *
     *     :validation: as performed by ``Encoding``
     */
    template <typename Encoding, typename It, typename St>
    auto decode_one(It first, St last, encoding_state_t<Encoding>& state) {
        return concepts::EncodingForm::decode_one<Encoding>(first, last, state);
    }

    namespace detail {
        template <typename Encoding, typename Rng>
        struct decoded_view
        : ranges::view_facade<
            decoded_view<Encoding, Rng>,
            ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value> {
        private:
            using base_type = ranges::view_facade<
                decoded_view<Encoding, Rng>,
                ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value>;

            CONCEPT_ASSERT(InputRangeOf<code_unit_t<Encoding>, Rng>());
            CONCEPT_ASSERT(EncodingForm<Encoding>());

            friend ranges::range_access;

            struct cursor;

            struct sentinel {
                sentinel() = default;
                sentinel(decoded_view const&, ranges::end_tag) {}
            };

            struct cursor {
            public:
                using reference = code_point;
                using difference_type = ranges::range_difference_t<Rng>;
                using single_pass = ranges::SinglePass<ranges::range_iterator_t<Rng>>;

                cursor() = default;
                cursor(decoded_view const& rng, ranges::begin_tag)
                : first(ranges::begin(rng.rng)), last(ranges::end(rng.rng))
                {}

                reference read() const {
                    if(decoded == invalid) {
                        decode_next();
                    }
                    assert(decoded != depleted);
                    return decoded;
                }

                void next() {
                    if(first == last) {
                        decoded = depleted;
                    } else {
                        decode_next();
                    }
                }

                bool equal(cursor const& pos) const {
                    assert(last == pos.last);
                    return first == pos.first;
                }

                bool equal(sentinel const&) const {
                    return decoded == depleted;
                }

            private:
                void decode_next() const {
                    std::tie(decoded, first) = decode_one<Encoding>(first, last, state);
                }

                static constexpr code_point invalid = -1;
                static constexpr code_point depleted = -2;

                mutable code_point decoded = invalid;
                mutable ranges::range_iterator_t<Rng> first;
                mutable encoding_state_t<Encoding> state {};
                ranges::range_iterator_t<Rng> last;
            };

            cursor begin_cursor() const {
                return { *this, ranges::begin_tag{} };
            }

            sentinel end_cursor() const {
                return { *this, ranges::end_tag{} };
            }

        public:
            decoded_view() = default;
            explicit decoded_view(Rng rng)
            : rng(std::move(rng))
            {}

        private:
            friend struct cursor;

            Rng rng;
        };
    } // namespace detail

    /**
     * .. function:: template <EncodingForm Encoding, ranges::Range Rng>\
     *               auto decode(Rng rng)
     *
     *     :returns: a range of the |code-points| that the |code-units| in ``rng`` represent
     *
     *     :validation: as performed by ``Encoding``
     */
    template <typename Encoding, typename Rng,
              CONCEPT_REQUIRES_(InputRangeOf<code_unit_t<Encoding>, Rng>()),
              CONCEPT_REQUIRES_(EncodingForm<Encoding>())>
    auto decode(Rng rng) {
        return detail::decoded_view<Encoding, Rng>(std::move(rng));
    }

    /**
     * .. type:: template <EncodingForm Encoding>\
     *           encoded_character
     *
     *     A container type for the |code-units| that encode a single
     *     |code-point| according to ``Encoding``.
     */
    template <typename Encoding>
    struct encoded_character
    : public detail::partial_array<code_unit_t<Encoding>, max_width_v<Encoding>> {
        using detail::partial_array<code_unit_t<Encoding>, max_width_v<Encoding>>::partial_array;
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_HPP
