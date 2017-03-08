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

#ifndef OGONEK_CONCEPTS_CORE_HPP
#define OGONEK_CONCEPTS_CORE_HPP

#include <range/v3/range_concepts.hpp>
#include <range/v3/utility/concepts.hpp>
#include <range/v3/utility/functional.hpp>

#include <iterator>
#include <type_traits>
#include <utility>

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
    } // namespace archetypes

    namespace concepts {
        using ranges::concepts::models;
        using ranges::concepts::refines;

        using ranges::concepts::valid_expr;
        using ranges::concepts::model_of;
        using ranges::concepts::is_true;
        using ranges::concepts::has_type;
        using ranges::concepts::convertible_to;

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

        struct ForwardRangeOf
        : refines<ForwardRange(_2)> {
        public:
            template <typename V, typename T>
            auto requires_(V&&, T&&) -> decltype(
                valid_expr(
                    is_true(std::is_same<V, ForwardRange::value_t<T>>())
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

        struct OptionalOf
        : refines<Optional(_2)> {
        public:
            template <typename V, typename T>
            auto requires_(V&&, T&&) -> decltype(
                valid_expr(
                    is_true(std::is_same<V, Optional::value_t<T>>())
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

    // TODO docs?
    template <typename T>
    using Optional = concepts::models<concepts::Optional, T>;
} // namespace ogonek

#endif // OGONEK_CONCEPTS_CORE_HPP
