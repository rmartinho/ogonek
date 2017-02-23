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

#ifndef OGONEK_DETAIL_NORMALIZATION_DECOMPOSED_HPP
#define OGONEK_DETAIL_NORMALIZATION_DECOMPOSED_HPP

#include <ogonek/concepts.h++>
#include <ogonek/ucd.h++>
#include <ogonek/detail/container/small_vector.h++>

#include <range/v3/view_facade.hpp>

namespace ogonek {
    namespace detail {
        template <typename Rng>
        struct decomposed_view
        : ranges::view_facade<
            decomposed_view<Rng>,
            ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value> {
        private:
            CONCEPT_ASSERT(InputRangeOf<code_point, Rng>());

        public:
            friend ranges::range_access;

            struct sentinel {
                sentinel() = default;
                sentinel(decomposed_view const&, ranges::end_tag) {}
            };

            struct cursor {
            private:
                using iterator = ranges::range_iterator_t<Rng>;

            public:
                using reference = code_point;
                using difference_type = ranges::range_difference_t<Rng>;
                using single_pass = ranges::SinglePass<iterator>;

                cursor() = default;
                cursor(decomposed_view const& rng, ranges::begin_tag)
                : first(ranges::begin(rng.rng)), last(ranges::end(rng.rng)) {
                    decompose_next();
                }

                reference read() const {
                    return decomposed[position];
                }

                void next() {
                    ++position;
                    if(position == static_cast<std::ptrdiff_t>(decomposed.size())) {
                        ++first;

                        decompose_next();
                    }
                }

                bool equal(cursor const& pos) const {
                    return first == pos.first && position == pos.position;
                }

                bool equal(sentinel const&) const {
                    return first == last;
                }

            private:
                void decompose_next() {
                    if(first != last) {
                        auto u = *first;
                        if(ucd::get_decomposition_type(u) == ucd::decomposition_type::canonical) {
                            // TODO internals that return small_vector directly
                            auto&& str = ucd::get_decomposition_mapping(u);
                            decomposed = decomposed_character(str.begin(), str.end());

                            auto is_starter = [](auto u) { return ucd::get_canonical_combining_class(u) == ucd::not_reordered; };
                            auto by_combining_class = [](auto a, auto b) {
                                return ucd::get_canonical_combining_class(a) < ucd::get_canonical_combining_class(b);
                            };
                            // TODO needs to be done on the entire stream below
                            auto l = decomposed.begin();
                            for(auto r = l; r != decomposed.end(); l = r) {
                                r = std::find_if(r+1, decomposed.end(), is_starter);
                                std::sort(l, r, by_combining_class);
                            }
                        } else {
                            decomposed = { u };
                        }
                        position = 0;
                    }
                }
                // TODO extract this pattern into some flat_map-ish range

                static constexpr auto max_decomposition = 18; // TODO generate this when code-generating UCD
                using decomposed_character = small_vector<code_point, max_decomposition>;

                iterator first;
                iterator last;
                decomposed_character decomposed;
                std::ptrdiff_t position = max_decomposition;
            };

            cursor begin_cursor() const {
                return { *this, ranges::begin_tag{} };
            }

            sentinel end_cursor() const {
                return { *this, ranges::end_tag{} };
            }

        public:
            decomposed_view() = default;
            decomposed_view(Rng rng)
            : rng(std::move(rng))
            {}

        private:
            friend struct cursor;

            Rng rng;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_NORMALIZATION_DECOMPOSED_HPP
