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
#include <ogonek/detail/static_const.h++>
#include <ogonek/detail/container/partial_array.h++>
#include <ogonek/detail/range/deferred.h++>

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
     * .. var:: template <EncodingForm Encoding>\
     *          constexpr auto max_width_v
     * 
     *     The maximum number of |code-units| needed by ``Encoding`` to
     *     represent one |code-point|.
     */
    template <typename Encoding>
    constexpr auto max_width_v = concepts::EncodingForm::max_width_v<Encoding>;

    /**
     * .. var:: template <EncodingForm Encoding>\
     *          constexpr auto replacement_character_v
     * 
     *     The character used to replace invalid input when
     *     :var:`replace_errors` is used for an encoding operation.
     *
     *     .. note:: Decoding always uses |u-fffd| to replace errors.
     */
    template <typename Encoding>
    constexpr auto replacement_character_v = concepts::EncodingForm::replacement_character_v<Encoding>;

    /**
     * .. type:: template <EncodingForm Encoding>\
     *           coding_state_t
     * 
     *     The type of the state used by ``Encoding``. For stateless encoding forms
     *     this is an empty type.
     */
    template <typename Encoding>
    using coding_state_t = typename concepts::EncodingForm::state_t<Encoding>;

    /**
     * .. type:: template <EncodingForm Encoding>\
     *           is_stateless
     * 
     *     Derives from ``std::true_type`` if ``Encoding`` is stateless; from
     *     ``std::false_type`` otherwise.
     */
    template <typename Encoding>
    using is_stateless = std::is_empty<coding_state_t<Encoding>>;

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
     *               coded_character_t<Encoding> encode_one(code_point u, coding_state_t<Encoding>& state)
     *
     *     Encodes ``u`` according to ``Encoding``.
     *
     *     :param u: the |code-point| to be encoded
     *
     *     :param state: the current encoding state; it is modified according to the encoding performed
     *
     *     :returns: a range of the |code-units| that encode ``u``
     *
     *     :throws: :type:`encode_error` when the input cannot be encoded by ``Encoding``
     */
    namespace fun {
        template <typename Encoding>
        struct encode_one {
            CONCEPT_ASSERT(EncodingForm<Encoding>());

            auto operator()(code_point u, coding_state_t<Encoding>& state) const {
                return concepts::EncodingForm::encode_one<Encoding>(u, state);
            }
        };
    } // namespace fun
    inline namespace {
        template <typename Encoding>
        constexpr auto const& encode_one = detail::static_const<fun::encode_one<Encoding>>::value;
    }

    /**
     * .. type:: template <EncodingForm Encoding>\
     *           coded_character_t
     * 
     *     Range of the |code-units| that encode one |code-point|.
     */
    template <typename Encoding>
    using coded_character_t = decltype(encode_one<Encoding>(std::declval<code_point>(), std::declval<coding_state_t<Encoding>&>()));

    namespace detail {
        template <typename Encoding, typename Rng, typename Handler>
        struct encoded_view
        : ranges::view_facade<
            encoded_view<Encoding, Rng, Handler>,
            ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value> {
        private:
            CONCEPT_ASSERT(InputRangeOf<code_point, Rng>());
            CONCEPT_ASSERT(EncodingForm<Encoding>());
            CONCEPT_ASSERT(EncodeErrorHandler<std::decay_t<Handler>, Encoding>());

            friend ranges::range_access;

            struct sentinel {
                sentinel() = default;
                sentinel(encoded_view const&, ranges::end_tag) {}
            };

            struct cursor {
            private:
                using code_unit = code_unit_t<Encoding>;
                using iterator = ranges::range_iterator_t<Rng>;

            public:
                using reference = code_unit;
                using difference_type = ranges::range_difference_t<Rng>;
                using single_pass = ranges::SinglePass<iterator>;

                cursor() = default;
                cursor(encoded_view const& rng, ranges::begin_tag)
                : first(ranges::begin(rng.rng)), last(ranges::end(rng.rng)) {
                    encode_next();
                }

                reference read() const {
                    return encoded[position];
                }

                void next() {
                    ++position;
                    if(position == static_cast<std::ptrdiff_t>(encoded.size())) {
                        ++first;

                        encode_next();
                    }
                }

                bool equal(cursor const& pos) const {
                    return first == pos.first && position == pos.position;
                }

                bool equal(sentinel const&) const {
                    return first == last;
                }

            private:
                void encode_next() {
                    while (first != last && position != 0) {
                        try {
                            encoded = encode_one<Encoding>(*first, state);
                            position = 0;
                        } catch(encode_error<Encoding> const& e) {
                            auto rep = (*handler)(e);
                            if(rep) {
                                encoded = encode_one<Encoding>(*rep, state);
                                position = 0;
                            } else {
                                ++first;
                            }
                        }
                    }
                }

                iterator first;
                iterator last;
                coded_character_t<Encoding> encoded;
                std::ptrdiff_t position = max_width_v<Encoding>;
                std::decay_t<Handler> const* handler = nullptr;
                coding_state_t<Encoding> state {};
            };

            cursor begin_cursor() const {
                return { *this, ranges::begin_tag{} };
            }

            sentinel end_cursor() const {
                return { *this, ranges::end_tag{} };
            }

        public:
            encoded_view() = default;
            encoded_view(Rng rng, Handler&& handler)
            : rng(std::move(rng)), handler(std::move(handler))
            {}

        private:
            friend struct cursor;

            Rng rng;
            std::decay_t<Handler> handler;
        };
    } // namespace detail

    /**
     * .. function:: template <EncodingForm Encoding, InputRange Rng, EncodeErrorHandler Handler>\
     *               auto encode(Rng rng, Handler&& handler)
     *
     *     :param rng: The range of |code-points| to encode
     *
     *     :param handler: The strategy for error handling
     *
     *     :returns: a range of the |code-units| that encode the |code-points| in ``rng``
     *
     *     :validation: as performed by ``Encoding``; errors are handled by ``handler``
     */
    namespace fun {
        template <typename Encoding>
        struct encode {
            CONCEPT_ASSERT(EncodingForm<Encoding>());

            template <typename Rng, typename Handler,
                      CONCEPT_REQUIRES_(InputRangeOf<code_point, Rng>()),
                      CONCEPT_REQUIRES_(EncodeErrorHandler<std::decay_t<Handler>, Encoding>())>
            auto operator()(Rng rng, Handler&& handler) const {
                return detail::defer(detail::encoded_view<Encoding, Rng, Handler>(std::move(rng), std::forward<Handler>(handler)));
            }
        };
    } // namespace fun
    inline namespace {
        template <typename Encoding>
        constexpr auto const& encode = detail::static_const<fun::encode<Encoding>>::value;
    }

    /**
     * .. function:: template <EncodingForm Encoding, Iterator It, Sentinel St>\
     *               std::pair<code_point, It> decode_one(It first, St last, coding_state_t<Encoding>& state)
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
     *     :throws: :type:`decode_error` when the input cannot be decoded by ``Encoding``
     */
    namespace fun {
        template <typename Encoding>
        struct decode_one {
            CONCEPT_ASSERT(EncodingForm<Encoding>());

            template <typename It, typename St>
            auto operator()(It first, St last, coding_state_t<Encoding>& state) const {
                return concepts::EncodingForm::decode_one<Encoding>(first, last, state);
            }
        };
    } // namespace fun
    inline namespace {
        template <typename Encoding>
        constexpr auto const& decode_one = detail::static_const<fun::decode_one<Encoding>>::value;
    }

    namespace detail {
        template <typename Encoding, typename Rng, typename Handler>
        struct decoded_view
        : ranges::view_facade<
            decoded_view<Encoding, Rng, Handler>,
            ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value> {
        private:
            using base_type = ranges::view_facade<
                decoded_view<Encoding, Rng, Handler>,
                ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value>;

            CONCEPT_ASSERT(EncodingForm<Encoding>());
            CONCEPT_ASSERT(InputRangeOf<code_unit_t<Encoding>, Rng>());
            CONCEPT_ASSERT(DecodeErrorHandler<std::decay_t<Handler>, Encoding>());

            friend ranges::range_access;

            struct sentinel {
                sentinel() = default;
                sentinel(decoded_view const&, ranges::end_tag) {}
            };

            struct cursor {
            private:
                using iterator = ranges::range_iterator_t<Rng>;

            public:
                using reference = code_point;
                using difference_type = ranges::range_difference_t<Rng>;
                using single_pass = ranges::SinglePass<iterator>;

                cursor() = default;
                cursor(decoded_view const& rng, ranges::begin_tag)
                : first(ranges::begin(rng.rng)), last(ranges::end(rng.rng)) {
                    decode_next();
                }

                reference read() const {
                    assert(decoded != invalid);
                    return decoded;
                }

                void next() {
                    decoded = invalid;
                    if(first != last) {
                        decode_next();
                    }
                }

                bool equal(cursor const& pos) const {
                    assert(last == pos.last);
                    return first == pos.first && (decoded == invalid) == (pos.decoded == invalid);
                }

                bool equal(sentinel const&) const {
                    return decoded == invalid;
                }

            private:
                void decode_next() {
                    while(first != last && decoded == invalid) {
                        try {
                            std::tie(decoded, first) = decode_one<Encoding>(first, last, state);
                        } catch(decode_error<Encoding> const& e) {
                            auto rep = (*handler)(e);
                            if(rep) {
                                decoded = *rep;
                            }
                            ++first; // TODO advance this from encoding itself?
                        }
                    }
                }

                static constexpr code_point invalid = -1; // TODO replace with optional

                iterator first;
                iterator last;
                code_point decoded = invalid;
                std::decay_t<Handler> const* handler = nullptr;
                coding_state_t<Encoding> state {};
            };

            cursor begin_cursor() const {
                return { *this, ranges::begin_tag{} };
            }

            sentinel end_cursor() const {
                return { *this, ranges::end_tag{} };
            }

        public:
            decoded_view() = default;
            decoded_view(Rng rng, Handler&& handler)
            : rng(std::move(rng)), handler(std::move(handler))
            {}

        private:
            friend struct cursor;

            Rng rng;
            std::decay_t<Handler> handler;
        };
    } // namespace detail

    /**
     * .. function:: template <EncodingForm Encoding, ranges::Range Rng>\
     *               auto decode(Rng rng)
     *
     *     :param rng: The range of |code-points| to encode
     *
     *     :param handler: The strategy for error handling
     *
     *     :returns: a range of the |code-points| that the |code-units| in ``rng`` represent
     *
     *     :validation: as performed by ``Encoding``; errors are handled by ``handler``
     */
    namespace fun {
        template <typename Encoding>
        struct decode {
            CONCEPT_ASSERT(EncodingForm<Encoding>());
            template <typename Rng, typename Handler,
                    CONCEPT_REQUIRES_(InputRangeOf<code_unit_t<Encoding>, Rng>()),
                    CONCEPT_REQUIRES_(DecodeErrorHandler<std::decay_t<Handler>, Encoding>())>
            auto operator()(Rng rng, Handler&& handler) const {
                return detail::defer(detail::decoded_view<Encoding, Rng, Handler>(std::move(rng), std::forward<Handler>(handler)));
            }
        };
    } // namespace fun
    inline namespace {
        template <typename Encoding>
        constexpr auto const& decode = detail::static_const<fun::decode<Encoding>>::value;
    }

    /**
     * .. type:: template <EncodingForm Encoding>\
     *           coded_character
     *
     *     A container type for the |code-units| that encode a single
     *     |code-point| according to ``Encoding``.
     */
    template <typename Encoding>
    struct coded_character
    : public detail::partial_array<code_unit_t<Encoding>, max_width_v<Encoding>> {
        using detail::partial_array<code_unit_t<Encoding>, max_width_v<Encoding>>::partial_array;
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_HPP
