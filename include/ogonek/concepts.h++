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

#include <range/v3/utility/concepts.hpp>

namespace ogonek {
    namespace concepts {
        using ranges::concepts::models;
        using ranges::concepts::refines;

        using ranges::concepts::valid_expr;
        using ranges::concepts::model_of;
        using ranges::concepts::is_true;

        using ranges::concepts::DefaultConstructible;
        using ranges::concepts::Integral;

        struct EncodingForm {
        private:
            template <typename T>
            using max_width_gt_zero_t = std::integral_constant<bool, (T::max_width > 0)>;

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
            static auto decode_one(It first, St last) { //, state_t<T>&) -> decltype(T::decode_one(first, last)) {
                return T::decode_one(first, last);
            }

            template<typename T>
            auto requires_(T&& t) -> decltype(
                valid_expr(
                    model_of<Integral, code_unit_t<T>>(),
                    model_of<DefaultConstructible, state_t<T>>(),
                    is_true(max_width_gt_zero_t<T>{}),
                    encode_one<T>(code_point(), std::declval<state_t<T>&>())
                ));
        };

        struct StatelessEncodingForm
            : refines<EncodingForm> {
        public:
            template <typename T>
            static auto encode_one(code_point u) {
                return T::encode_one(u);
            }

            template<typename T>
            auto requires_(T&& t) -> decltype(
                valid_expr(
                    is_true(std::is_empty<state_t<T>>{})
                ));
        };
    } // namespace concepts

    /**
     * .. concept:: Type{E} EncodingForm
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

    template <typename T>
    using StatelessEncodingForm = concepts::models<concepts::StatelessEncodingForm, T>;
} // namespace ogonek

#endif // OGONEK_CONCEPTS_HPP
