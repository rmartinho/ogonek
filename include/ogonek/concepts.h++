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
 * Concepts ``<ogonek/concepts.h++>``
 * ==================================
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

#include <cstddef>

namespace ogonek {
    namespace archetypes {
        template <typename T>
        struct InputIterator {
            using value_type = T;
            using reference = T&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::input_iterator_tag;

            InputIterator& operator++();
            void operator++(int);
            T operator*() const;
        };
        template <typename T, typename I = InputIterator<T>>
        struct Sentinel {
            friend bool operator==(Sentinel const&, I const&);
            friend bool operator!=(Sentinel const&, I const&);
            friend bool operator==(I const&, Sentinel const&);
            friend bool operator!=(I const&, Sentinel const&);
        };

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

        using ranges::concepts::Range;
        using ranges::concepts::InputRange;

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

            template<typename T>
            auto requires_(T&&) -> decltype(
                valid_expr(
                    model_of<Integral, code_unit_t<T>>(),
                    model_of<SemiRegular, state_t<T>>(),
                    is_true(std::integral_constant<bool, (max_width_v<T> > 0)>{}),
                    encode_one<T>(code_point(), std::declval<state_t<T>&>()),
                    //encode_one<T>(code_point(), std::declval<state_t<T>&>(), std::declval<assume_valid_t>()),
                    decode_one<T>(archetypes::InputIterator<code_unit_t<T>>(),
                                  archetypes::Sentinel<code_unit_t<T>>(),
                                  std::declval<state_t<T>&>())
                    //decode_one<T>(archetypes::InputIterator<code_unit_t<T>>(),
                    //              archetypes::Sentinel<code_unit_t<T>>(),
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

            template<typename T>
            auto requires_(T&&) -> decltype(
                valid_expr(
                    is_true(std::is_empty<state_t<T>>())
                ));
        };

        struct Optional {
        public:
            template <typename T>
            using value_t = std::remove_reference_t<decltype(*std::declval<T const&>())>;

            template<typename T>
            auto requires_(T&&) -> decltype(
                valid_expr(
                    model_of<DefaultConstructible, T>(),
                    *std::declval<T const&>(),
                    static_cast<bool>(std::declval<T const&>())
                ));
        };

        struct InputRangeOf
        : refines<InputRange(_2)> {
        public:
            template<typename V, typename T>
            auto requires_(V&&, T&&) -> decltype(
                valid_expr(
                    is_true(std::is_same<V, InputRange::value_t<T>>())
                ));
        };

        struct OptionalOf
        : refines<Optional(_2)> {
        public:
            template<typename V, typename T>
            auto requires_(V&&, T&&) -> decltype(
                valid_expr(
                    is_true(std::is_same<V, Optional::value_t<T>>())
                ));
        };

        struct EncodeErrorHandler {
        public:
            template<typename H, typename E,
                     typename HandlerResult = Invocable::result_t<H const&, encode_error<E>>>
            auto requires_(H&&, E&&) -> decltype(
                valid_expr(
                    model_of<Invocable, H const&, encode_error<E>>(),
                    model_of<OptionalOf, code_point, HandlerResult>()
                ));
        };

        struct DecodeErrorHandler {
        public:
            template<typename H, typename E,
                     typename HandlerResult = Invocable::result_t<H const&, decode_error<E>>>
            auto requires_(H&&, E&&) -> decltype(
                valid_expr(
                    model_of<Invocable, H const&, decode_error<E>>(),
                    model_of<OptionalOf, code_point, HandlerResult>()
                ));
        };
    } // namespace concepts

    using ranges::Invocable;

    using ranges::Range;
    using ranges::InputRange;

    // TODO docs?
    template <typename V, typename T>
    using InputRangeOf = concepts::models<concepts::InputRangeOf, V, T>;

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
} // namespace ogonek

#endif // OGONEK_CONCEPTS_HPP
