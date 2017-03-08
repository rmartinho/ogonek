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
 * =============
 */

#ifndef OGONEK_SEGMENTATION_HPP
#define OGONEK_SEGMENTATION_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts/segmentation.h++>
#include <ogonek/detail/static_const.h++>
#include <ogonek/detail/container/lookahead_window.h++>

#include <range/v3/range_traits.hpp>
#include <range/v3/begin_end.hpp>

#include <cstddef>

namespace ogonek {
    /**
     * .. var:: template <BoundaryCondition Break>\
     *          constexpr auto max_lookbehind_v
     * 
     *     The maximum number of |code-points| preceding a position that need
     *     to be checked to determine whether a boundary exists according to
     *     ``Break``.
     */
    template <typename Break>
    constexpr auto max_lookbehind_v = concepts::BoundaryCondition::max_lookbehind_v<Break>;

    /**
     * .. var:: template <BoundaryCondition Break>\
     *          constexpr auto max_lookahead_v
     * 
     *     The maximum number of |code-points| succeeding a position that need
     *     to be checked to determine whether a boundary exists according to
     *     ``Break``.
     */
    template <typename Break>
    constexpr auto max_lookahead_v = concepts::BoundaryCondition::max_lookahead_v<Break>;

    /**
     * .. function:: template <BoundaryCondition Break>\
     *               bool is_boundary_ignorable(code_point previous, code_point current)
     *
     *     .. warning:: |unstable-api|
     *
     *     Tests whether a |code-point| is ignorable when determining boundaries.
     *
     *     :param previous: the |code-point| that occurs before the one being tested
     *
     *     :param current: the |code-point| being tested
     *
     *     :returns: true if ``current`` can be ignored to determine boundaries
     *               when following ``previous``; false otherwise.
     */
    namespace fun {
        template <typename Break>
        struct is_boundary_ignorable {
            CONCEPT_ASSERT(BoundaryCondition<Break>());

            auto operator()(code_point previous, code_point current) const {
                return concepts::BoundaryCondition::is_boundary_ignorable<Break>(previous, current);
            }
        };
    } // namespace fun
    inline namespace {
        template <typename Break>
        constexpr auto const& is_boundary_ignorable = detail::static_const<fun::is_boundary_ignorable<Break>>::value;
    }

    /**
     * .. function:: template <BoundaryCondition Break, RandomAccessRange Rng>\
     *               bool is_boundary(Rng rng)
     *
     *     .. warning:: |unstable-api|
     *
     *     Tests whether a boundary exists at a given position in a range of
     *     |code-points|.
     *
     *     :param rng: the range of |code-points| to check for a boundary. This
     *                 range contains some |code-points| before the position to
     *                 be checked and some after it, as determined by
     *                 var:`max_lookbehind_v` and var:`max_lookahead_v`.
     *
     *     :returns: true if a boundary exists at the position checked,
     *               according to ``Break``; false otherwise.
     */
    namespace fun {
        template <typename Break>
        struct is_boundary {
            CONCEPT_ASSERT(BoundaryCondition<Break>());

            template <typename Rng>
            auto operator()(Rng rng) const {
                return concepts::BoundaryCondition::is_boundary<Break>(rng);
            }
        };
    } // namespace fun
    inline namespace {
        template <typename Break>
        constexpr auto const& is_boundary = detail::static_const<fun::is_boundary<Break>>::value;
    }

    namespace detail {
        template <typename Break, typename Rng>
        struct boundary_view
        : ranges::view_facade<
            boundary_view<Break, Rng>,
            ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value> {
        private:
            CONCEPT_ASSERT(BoundaryCondition<Break>());
            CONCEPT_ASSERT(ForwardRangeOf<code_point, Rng>());

            friend ranges::range_access;

            struct sentinel {
                sentinel() = default;
                sentinel(boundary_view const&, ranges::end_tag) {}
            };

            struct cursor {
            private:
                using iterator = ranges::range_iterator_t<Rng>;

            public:
                using reference = iterator;
                using difference_type = std::ptrdiff_t;
                using single_pass = ranges::SinglePass<iterator>;

                cursor() = default;
                cursor(boundary_view const& rng, ranges::begin_tag)
                : first(ranges::begin(rng.rng)), last(ranges::end(rng.rng)) {}

                reference read() const {
                    return first;
                }

                void next() {
                    ++first;
                }

                bool equal(cursor const& pos) const {
                    return first == pos.first;
                }

                bool equal(sentinel const&) const {
                    return first == last;
                }

            private:
                using window_type = detail::lookahead_window<iterator, max_lookbehind_v<Break>, max_lookahead_v<Break>>;

                void skip_ignores() {
                    window_type window(first, last);

                    do {
                        for(int i = -1; i < max_lookahead_v<Break>; ++i) {
                            if(is_boundary_ignorable<Break>(window[i], window[i+1])) {
                                window.skip(i+1);
                            }
                        }
                        if(is_boundary<Break>(window)) {
                            break;
                        }
                        window.advance();
                    } while(true);

                    first = window.position();
                }

                iterator first;
                iterator last;
            };

            cursor begin_cursor() const {
                return { *this, ranges::begin_tag{} };
            }

            sentinel end_cursor() const {
                return { *this, ranges::end_tag{} };
            }

        public:
            boundary_view() = default;
            boundary_view(Rng rng)
            : rng(std::move(rng))
            {}

        private:
            friend struct cursor;

            Rng rng;
        };
    } // namespace detail
    /**
     * .. function:: template <typename Break, typename Rng>\
     *               auto boundaries(Rng rng)
     *
     *     ..todo:: docs
     */
    namespace fun {
        template <typename Break>
        struct boundaries {
            template <typename Rng>
            auto operator()(Rng rng) const {
                return detail::boundary_view<Break, Rng>(rng);
            }
        };
    } // namespace fun
    inline namespace {
        template <typename Break>
        constexpr auto const& boundaries = detail::static_const<fun::boundaries<Break>>::value;
    }
} // namespace ogonek

#endif // OGONEK_SEGMENTATION_HPP
