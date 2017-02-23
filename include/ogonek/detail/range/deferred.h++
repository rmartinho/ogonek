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

// Range adaptor that defers starting the range

#ifndef OGONEK_DETAIL_RANGE_DEFERRED_HPP
#define OGONEK_DETAIL_RANGE_DEFERRED_HPP

#include <ogonek/concepts.h++>
#include <ogonek/detail/container/either.h++>

#include <range/v3/view_facade.hpp>

namespace ogonek {
    namespace detail {
        template <typename Rng>
        struct deferred_view
        : ranges::view_facade<
            deferred_view<Rng>,
            ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value> {
        private:
            CONCEPT_ASSERT(Range<Rng>());

            friend ranges::range_access;

            struct sentinel {
                sentinel() = default;
                sentinel(deferred_view const&, ranges::end_tag) {}
            };

            struct cursor {
            public:
                using reference = code_point;
                using difference_type = ranges::range_difference_t<Rng>;
                using single_pass = ranges::SinglePass<ranges::range_iterator_t<Rng>>;

                cursor()
                : state(state_t::make_left(nullptr)) {}
                cursor(deferred_view const& rng, ranges::begin_tag)
                : state(state_t::make_left(&rng.rng)) {}

                reference read() const {
                    ensure_started();
                    return *state.as_right().first;
                }

                void next() {
                    ensure_started();
                    ++state.as_right().first;
                }

                bool equal(cursor const& pos) const {
                    ensure_started();
                    pos.ensure_started();
                    return state.as_right().first == pos.state.as_right().first;
                }

                bool equal(sentinel const&) const {
                    ensure_started();
                    return state.as_right().first == state.as_right().last;
                }

            private:
                void ensure_started() const {
                    if(state.is_left()) {
                        auto& rng = *state.as_left();
                        auto first = ranges::begin(rng);
                        auto last = ranges::end(rng);
                        state.place_right(iterating { first, last });
                    }
                }

                using iterator = ranges::range_iterator_t<Rng>;
                using sentinel = ranges::range_sentinel_t<Rng>;
               
                struct iterating {
                    iterator first;
                    sentinel last;
                };
                using state_t = either<Rng const*, iterating>;
                mutable state_t state;
            };

            cursor begin_cursor() const {
                return { *this, ranges::begin_tag{} };
            }

            sentinel end_cursor() const {
                return { *this, ranges::end_tag{} };
            }

        public:
            deferred_view() = default;
            deferred_view(Rng rng)
            : rng(std::move(rng))
            {}

        private:
            friend struct cursor;

            Rng rng;
        };

        template <typename Rng,
                CONCEPT_REQUIRES_(Range<Rng>())>
        auto defer(Rng rng) {
            return deferred_view<Rng>(std::move(rng));
        }
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_RANGE_DEFERRED_HPP
