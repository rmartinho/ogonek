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
 * Normalization
 * =============
 */

#ifndef OGONEK_CONCEPTS_NORMALIZATION_HPP
#define OGONEK_CONCEPTS_NORMALIZATION_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts/core.h++>

#include <type_traits>
#include <utility>

#include <range/v3/begin_end.hpp>

namespace ogonek {
    namespace concepts {
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

