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

                cursor() = default;
                cursor(deferred_view const& rng, ranges::begin_tag)
                : rng(&rng.rng)
                {}

                reference read() const {
                    ensure_started();
                    return *first;
                }

                void next() {
                    ensure_started();
                    ++first;
                }

                bool equal(cursor const& pos) const {
                    ensure_started();
                    pos.ensure_started();
                    return first == pos.first;
                }

                bool equal(sentinel const&) const {
                    ensure_started();
                    return first == last;
                }

            private:
                void ensure_started() const {
                    if(!started) {
                        first = ranges::begin(*rng);
                        last = ranges::end(*rng);
                        started = true;
                    }
                }

                using iterator = ranges::range_iterator_t<Rng>;
                using sentinel = ranges::range_sentinel_t<Rng>;
               
                Rng const* rng;
                mutable iterator first;
                mutable sentinel last;
                mutable bool started = false;
                //struct iterating {
                //    iterator first;
                //    sentinel last;
                //};
                //variant<Rng const*, iterating> it;
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
