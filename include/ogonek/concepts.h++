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
 * Concepts
 * ========
 */

#ifndef OGONEK_CONCEPTS_HPP
#define OGONEK_CONCEPTS_HPP

#include <ogonek/types.h++>
#include <ogonek/error_fwd.h++>

#include <range/v3/range_concepts.hpp>
#include <range/v3/utility/concepts.hpp>
#include <range/v3/utility/functional.hpp>

#include <iterator>
#include <array>
#include <type_traits>

#include <cstddef>

namespace ogonek {
    namespace detail {
        template <typename...>
        struct always_true : std::true_type {};
    } // namespace detail
    namespace archetypes {
        template <typename T>
        struct ForwardIterator {
            using value_type = T;
            using reference = T&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            ForwardIterator& operator++();
            void operator++(int);
            T operator*() const;
        };
        template <typename T, typename I = ForwardIterator<T>>
        struct ForwardSentinel {
            friend bool operator==(ForwardSentinel const&, I const&);
            friend bool operator!=(ForwardSentinel const&, I const&);
            friend bool operator==(I const&, ForwardSentinel const&);
            friend bool operator!=(I const&, ForwardSentinel const&);
        };
        template <typename T>
        struct OutputIterator {
            using value_type = T;
            using reference = T&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::output_iterator_tag;

            OutputIterator& operator++();
            OutputIterator operator++(int);
            T& operator*() const;
        };
        //CONCEPT_ASSERT(ranges::WeaklyIncrementable<OutputIterator<int>>());
        //CONCEPT_ASSERT(ranges::Iterator<OutputIterator<int>>());
        //CONCEPT_ASSERT(ranges::Movable<OutputIterator<int>>());
        //CONCEPT_ASSERT(ranges::DefaultConstructible<OutputIterator<int>>());
        //CONCEPT_ASSERT(ranges::Writable<OutputIterator<int>, int>());
        CONCEPT_ASSERT(ranges::OutputIterator<OutputIterator<code_point>, code_point>());

        template <typename Encoding>
        struct EncodeErrorHandler {
            code_point* operator()(encode_error<Encoding>) const;
        };

        template <typename Encoding>
        struct DecodeErrorHandler {
            code_point* operator()(decode_error<Encoding>) const;
        };

        struct EncodingForm {
            using code_unit = int;
            using state = int;
            static std::array<code_unit, 1> encode_one(code_point, state&);
            template <typename It, typename St>
            static std::pair<code_point, It> decode_one(It, St, state&);
        };
    } // namespace archetypes

    namespace concepts {
        using ranges::concepts::models;
        using ranges::concepts::refines;

        using ranges::concepts::valid_expr;
        using ranges::concepts::model_of;
        using ranges::concepts::is_true;
        using ranges::concepts::has_type;

        using ranges::concepts::DefaultConstructible;
        using ranges::concepts::Same;
        using ranges::concepts::SemiRegular;
        using ranges::concepts::ConvertibleTo;
        using ranges::concepts::Integral;
        using ranges::concepts::Invocable;

        using ranges::concepts::_1;
        using ranges::concepts::_2;

        using ranges::concepts::OutputIterator;
        using ranges::concepts::ForwardRange;

        struct EncodingForm {
        private:
            template <typename T>
            struct max_width {
                template <typename U = T>
                static std::integral_constant<std::size_t, U::max_width> test(int);
                static std::integral_constant<std::size_t, 1> test(...);
                using type = decltype(test(0));
                static constexpr std::size_t value = type::value;
            };

            template <typename T>
            struct replacement_character {
                template <typename U = T>
                static std::integral_constant<char32_t, U::replacement_character> test(int);
                static std::integral_constant<char32_t, U'\uFFFD'> test(...);
                using type = decltype(test(0));
                static constexpr std::size_t value = type::value;
            };

            template <typename T>
            struct state {
                struct empty {};
                template <typename U = T>
                static typename U::state test(int);
                static empty test(...);
                using type = decltype(test(0));
            };

        public:
            template <typename T>
            using code_unit_t = typename T::code_unit;

            template <typename T>
            static constexpr std::size_t max_width_v = max_width<T>::value;

            template <typename T>
            static constexpr char32_t replacement_character_v = replacement_character<T>::value;

            template <typename T>
            using state_t = typename state<T>::type;

            template <typename T>
            static auto encode_one(code_point u, state_t<T>& s) -> decltype(T::encode_one(u, s)) {
                return T::encode_one(u, s);
            }

            template <typename T>
            static auto encode_one(code_point u, state_t<T>&) -> decltype(T::encode_one(u)) {
                return T::encode_one(u);
            }

            template <typename T, typename It, typename St>
            static auto decode_one(It it, St st, state_t<T>& s) -> decltype(T::decode_one(it, st, s)) {
                return T::decode_one(it, st, s);
            }

            template <typename T, typename It, typename St>
            static auto decode_one(It it, St st, state_t<T>&) -> decltype(T::decode_one(it, st)) {
                return T::decode_one(it, st);
            }

            template <typename T>
            auto requires_(T&&) -> decltype(
                valid_expr(
                    model_of<Integral, code_unit_t<T>>(),
                    model_of<SemiRegular, state_t<T>>(),
                    is_true(std::integral_constant<bool, (max_width_v<T> > 0)>{}),
                    encode_one<T>(code_point(), std::declval<state_t<T>&>()),
                    // TODO encode_one<T>(code_point(), std::declval<state_t<T>&>(), std::declval<assume_valid_t>()),
                    decode_one<T>(archetypes::ForwardIterator<code_unit_t<T>>(),
                                  archetypes::ForwardSentinel<code_unit_t<T>>(),
                                  std::declval<state_t<T>&>())
                    // TODO decode_one<T>(archetypes::ForwardIterator<code_unit_t<T>>(),
                    //              archetypes::ForwardSentinel<code_unit_t<T>>(),
                    //              std::declval<state_t<T>&>(),
                    //              std::declval<assume_valid_t>())
                ));
        };

        struct StatelessEncodingForm
            : refines<EncodingForm> {
        public:
            template <typename T>
            static auto encode_one(code_point u) {
                return T::encode_one(u);
            }

            template <typename T, typename It, typename St>
            static auto decode_one(It it, St st) {
                return T::decode_one(it, st);
            }

            template <typename T>
            auto requires_(T&&) -> decltype(
                valid_expr(
                    is_true(std::is_empty<state_t<T>>())
                ));
        };

        struct Optional {
        public:
            template <typename T>
            using value_t = std::remove_reference_t<decltype(*std::declval<T const&>())>;

            template <typename T>
            auto requires_(T&&) -> decltype(
                valid_expr(
                    model_of<DefaultConstructible, T>(),
                    *std::declval<T const&>(),
                    static_cast<bool>(std::declval<T const&>())
                ));
        };

        struct ForwardRangeOf
        : refines<ForwardRange(_2)> {
        public:
            template <typename V, typename T>
            auto requires_(V&&, T&&) -> decltype(
                valid_expr(
                    is_true(std::is_same<V, ForwardRange::value_t<T>>())
                ));
        };

        struct OptionalOf
        : refines<Optional(_2)> {
        public:
            template <typename V, typename T>
            auto requires_(V&&, T&&) -> decltype(
                valid_expr(
                    is_true(std::is_same<V, Optional::value_t<T>>())
                ));
        };

        struct EncodeErrorHandler {
        public:
            template <typename H, typename E,
                     typename HandlerResult = Invocable::result_t<H const&, encode_error<E>>>
            auto requires_(H&&, E&&) -> decltype(
                valid_expr(
                    model_of<Invocable, H const&, encode_error<E>>(),
                    model_of<OptionalOf, code_point, HandlerResult>()
                ));
        };

        struct DecodeErrorHandler {
        public:
            template <typename H, typename E,
                     typename HandlerResult = Invocable::result_t<H const&, decode_error<E>>>
            auto requires_(H&&, E&&) -> decltype(
                valid_expr(
                    model_of<Invocable, H const&, decode_error<E>>(),
                    model_of<OptionalOf, code_point, HandlerResult>()
                ));
        };

        struct NormalizationForm {
        private:
            template <typename T, typename Rng>
            struct has_compose_tester {
                template <typename U = T>
                static auto test(int) -> detail::always_true<decltype(U::compose(std::declval<Rng>()))>;
                static auto test(...) -> std::false_type;
                using type = decltype(test(0));
            };
            template <typename T, typename Rng>
            struct has_compose : has_compose_tester<T, Rng>::type {};

            template <typename T, typename Rng>
            static auto compose(Rng rng, std::true_type) {
                return T::compose(rng);
            }
            template <typename T, typename Rng>
            static auto compose(Rng rng, std::false_type) {
                return ranges::end(rng);
            }

        public:
            template <typename T, typename Out>
            static auto decompose_into(code_point u, Out out) -> decltype(T::decompose_into(u, out)) {
                return T::decompose_into(u, out);
            }
            template <typename T, typename Rng>
            static auto compose(Rng rng) {
                return NormalizationForm::compose<T>(rng, has_compose<T, Rng>());
            }

            template <typename N>
            auto requires_(N&&) -> decltype(
                valid_expr(
                    (decompose_into<N>(code_point(), archetypes::OutputIterator<code_point>()), 42)
                ));
        };
    } // namespace concepts

    using ranges::ForwardIterator;
    using ranges::OutputIterator;
    using ranges::Sentinel;
    using ranges::ForwardRange;
    using ranges::OutputRange;

    // TODO docs?
    template <typename V, typename T>
    using ForwardRangeOf = concepts::models<concepts::ForwardRangeOf, V, T>;

    /**
     * .. concept:: template <typename E>\
     *              EncodingForm
     * 
     *     An |encoding-form| type. It describes an encoding form's mapping
     *     between |code-points| and |code-units|, as well as some extra
     *     properties which are used for checking constraints and for
     *     performing optimizations.
     *
     *     .. todo:: Document requirements
     */
    template <typename T>
    using EncodingForm = concepts::models<concepts::EncodingForm, T>;

    /**
     * .. concept:: template <typename E>\
     *              StatelessEncodingForm
     * 
     *     An |encoding-form| that requires no state for encoding/decoding
     *     operations.
     *
     *     .. todo:: Document requirements
     */
    template <typename T>
    using StatelessEncodingForm = concepts::models<concepts::StatelessEncodingForm, T>;

    /**
     * .. concept:: template <typename O>\
     *              Optional
     * 
     *     A type of objects that contain an optional value.
     *
     *     .. todo:: Document requirements
     */
    template <typename T>
    using Optional = concepts::models<concepts::Optional, T>;

    /**
     * .. concept:: template <typename H, typename E>\
     *              EncodeErrorHandler
     *
     *     ``H`` is an error handler that can handle errors when encoding with ``E``.
     *
     *     .. todo:: Document requirements
     */
    template <typename H, typename E>
    using EncodeErrorHandler = concepts::models<concepts::EncodeErrorHandler, H, E>;

    /**
     * .. concept:: template <typename H, typename E>\
     *              DecodeErrorHandler
     *
     *     ``H`` is an error handler that can handle errors when encoding with ``E``.
     *
     *     .. todo:: Document requirements
     */
    template <typename H, typename E>
    using DecodeErrorHandler = concepts::models<concepts::DecodeErrorHandler, H, E>;

    /**
     * .. concept:: template <typename N>\
     *              NormalizationForm
     *
     *     ``N`` is a Unicode normalization form.
     *
     *     .. todo:: Document requirements
     */
    template <typename N>
    using NormalizationForm = concepts::models<concepts::NormalizationForm, N>;
} // namespace ogonek

#endif // OGONEK_CONCEPTS_HPP
