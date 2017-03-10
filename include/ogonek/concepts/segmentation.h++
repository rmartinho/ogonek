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
 * Segmentation
 * ============
 */

#ifndef OGONEK_CONCEPTS_SEGMENTATION_HPP
#define OGONEK_CONCEPTS_SEGMENTATION_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts/core.h++>

#include <range/v3/begin_end.hpp>

#include <type_traits>
#include <utility>
#include <vector>

#include <cstddef>

namespace ogonek {
    namespace concepts {
        struct BoundaryCondition {
        private:
            template <typename T>
            struct max_lookbehind {
                template <typename U = T>
                static std::integral_constant<std::size_t, U::max_lookbehind> test(int);
                static std::integral_constant<std::size_t, 1> test(...);
                using type = decltype(test(0));
                static constexpr std::size_t value = type::value;
            };


            template <typename T>
            struct max_lookahead {
                template <typename U = T>
                static std::integral_constant<std::size_t, U::max_lookahead> test(int);
                static std::integral_constant<std::size_t, 1> test(...);
                using type = decltype(test(0));
                static constexpr std::size_t value = type::value;
            };

            template <typename T>
            struct has_is_boundary_ignorable_tester {
                template <typename U = T>
                static auto test(int)
                    -> detail::always_true<decltype(U::is_boundary_ignorable(U'\0', U'\0'))>;
                static auto test(...) -> std::false_type;
                using type = decltype(test(0));
            };
            template <typename T>
            struct has_is_boundary_ignorable : has_is_boundary_ignorable_tester<T>::type {};

            template <typename T>
            static auto is_boundary_ignorable(code_point previous, code_point current, std::true_type) {
                return T::is_boundary_ignorable(previous, current);
            }
            template <typename T>
            static auto is_boundary_ignorable(code_point, code_point, std::false_type) {
                return false;
            }

            template <typename T, typename Rng, std::size_t... I>
            static auto is_boundary(Rng rng, std::index_sequence<I...>) {
                return T::is_boundary(rng[I]...);
            }

        public:
            template <typename T>
            static constexpr std::size_t max_lookbehind_v = max_lookbehind<T>::value;

            template <typename T>
            static constexpr std::size_t max_lookahead_v = max_lookahead<T>::value;

            template <typename T>
            static auto is_boundary_ignorable(code_point previous, code_point current) {
                return BoundaryCondition::is_boundary_ignorable<T>(previous, current, has_is_boundary_ignorable<T>());
            }

            template <typename T, typename Rng>
            static auto is_boundary(Rng rng) {
                constexpr auto len = max_lookbehind_v<T> + max_lookahead_v<T>;
                return BoundaryCondition::is_boundary<T>(rng, std::make_index_sequence<len>());
            }

            template <typename N>
            auto requires_(N&&) -> decltype(
                valid_expr(
                    convertible_to<bool>(is_boundary<N>(std::vector<code_point>())) // TODO RAR archetype
                ));
        };
    } // namespace concepts

    /**
     * .. concept:: template <typename N>\
     *              BoundaryCondition
     *
     *     A condition that determines boundaries between code points.
     *
     *     .. todo:: Document requirements
     */
    template <typename N>
    using BoundaryCondition = concepts::models<concepts::BoundaryCondition, N>;
} // namespace ogonek

#endif // OGONEK_CONCEPTS_SEGMENTATION_HPP
