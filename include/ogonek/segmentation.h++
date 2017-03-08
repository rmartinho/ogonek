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
#include <ogonek/concepts.h++>
#include <ogonek/detail/static_const.h++>

#include <range/v3/range_traits.hpp>
#include <range/v3/begin_end.hpp>

#include <cstddef>

namespace ogonek {
    namespace detail {
        template <typename Break, typename Rng>
        struct boundary_view
        : ranges::view_facade<
            boundary_view<Break, Rng>,
            ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value> {
        private:
            //CONCEPT_ASSERT(BoundaryCondition<Break>());
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
