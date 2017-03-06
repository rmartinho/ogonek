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

#ifndef OGONEK_NORMALIZATION_HPP
#define OGONEK_NORMALIZATION_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts.h++>
#include <ogonek/ucd.h++>
#include <ogonek/detail/static_const.h++>
#include <ogonek/detail/container/small_vector.h++>

#include <range/v3/view_facade.hpp>
#include <range/v3/utility/iterator.hpp>
#include <range/v3/view/all.hpp>

#include <algorithm>
#include <iterator>

namespace ogonek {
    /**
     * .. function:: template <NormalizationForm Form, OutputIterator Out>\
     *               auto decompose_into(code_point u, Out out)
     *
     *     Writes the full decomposition of a |code-point| into an output iterator,
     *     according to ``Form``.
     *
     *     :param u: The |code-points| to decompose
     *
     *     :param out: The iterator to write to
     */
    namespace fun {
        template <typename Form>
        struct decompose_into {
            CONCEPT_ASSERT(NormalizationForm<Form>());

            template <typename Out,
                    CONCEPT_REQUIRES_(OutputIterator<Out, code_point>())>
            void operator()(code_point u, Out out) const {
                concepts::NormalizationForm::decompose_into<Form>(u, out);
            }
        };
    } // namespace fun
    inline namespace {
        template <typename Form>
        constexpr auto const& decompose_into = detail::static_const<fun::decompose_into<Form>>::value;
    }

    // TODO OutputRange requirement
    /**
     * .. function:: template <NormalizationForm Form, ForwardRange Rng>\
     *               auto compose(Rng rng)
     *
     *     Applies the Canonical Composition Algorithm to range.
     *
     *     :param rng: A range of |code-points|
     *
     *     :returns: A canonically-composed subrange of ``rng``
     */
    namespace fun {
        template <typename Form>
        struct compose {
            CONCEPT_ASSERT(NormalizationForm<Form>());

            template <typename Rng,
                    CONCEPT_REQUIRES_(ForwardRangeOf<code_point, Rng>()),
                    CONCEPT_REQUIRES_(OutputRange<Rng, code_point>())>
            auto operator()(Rng rng) const {
                return concepts::NormalizationForm::compose<Form>(rng);
            }
        };
    } // namespace fun
    inline namespace {
        template <typename Form>
        constexpr auto const& compose = detail::static_const<fun::compose<Form>>::value;
    }

    namespace detail {
        template <typename Form, typename Rng>
        struct normalized_view
        : ranges::view_facade<
                normalized_view<Form, Rng>,
                ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value> {
        private:
            CONCEPT_ASSERT(NormalizationForm<Form>());
            CONCEPT_ASSERT(ForwardRangeOf<code_point, Rng>());

        public:
            friend ranges::range_access;

            struct sentinel {
                sentinel() = default;
                sentinel(normalized_view const&, ranges::end_tag) {}
            };

            struct cursor {
            private:
                using iterator = ranges::range_iterator_t<Rng>;

            public:
                using reference = code_point;
                using difference_type = ranges::range_difference_t<Rng>;
                using single_pass = ranges::SinglePass<iterator>;

                cursor() = default;
                cursor(normalized_view const& rng, ranges::begin_tag)
                        : first(ranges::begin(rng.rng)), last(ranges::end(rng.rng)) {
                    decompose_next();
                }

                reference read() const {
                    return decomposed[position];
                }

                void next() {
                    ++position;
                    if(position == static_cast<std::ptrdiff_t>(decomposed.size())) {
                        decompose_next();
                    }
                }

                bool equal(cursor const& pos) const {
                    return first == pos.first && position == pos.position;
                }

                bool equal(sentinel const&) const {
                    return decomposed.size() == 0;
                }

            private:
                void decompose_next() {
                    decomposed.clear();
                    if(first != last) {
                        // TODO support input ranges
                        auto is_decomposition_boundary = [](auto u) {
                            return ucd::get_canonical_combining_class(u) == ucd::not_reordered && ucd::get_hangul_syllable_type(u) != ucd::hangul_syllable_type::t;
                        };
                        auto is_starter = [](auto u) {
                            return ucd::get_canonical_combining_class(u) == ucd::not_reordered;
                        };
                        auto by_canonical_combining_class = [](auto a, auto b) {
                            return ucd::get_canonical_combining_class(a) < ucd::get_canonical_combining_class(b);
                        };

                        auto next_boundary = std::find_if(std::next(first), last, is_decomposition_boundary);
                        for(; first != next_boundary; ++first) {
                            decompose_into<Form>(*first, ranges::back_inserter(decomposed));
                        }
                        // TODO optimize for no-starter decompositions
                        auto l = decomposed.begin();
                        for(auto r = l; r != decomposed.end(); l = r) {
                            r = std::find_if(std::next(r), decomposed.end(), is_starter);
                            std::sort(l, r, by_canonical_combining_class);
                        }

                        auto end = compose<Form>(ranges::view::all(decomposed));
                        decomposed.erase(end, decomposed.end());

                        position = 0;
                    }
                }
                // TODO extract this pattern into some flat_map-ish range

                static constexpr auto max_decomposition = 18; // TODO generate this when code-generating UCD
                using decomposed_character = small_vector<code_point, 4>;

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
            normalized_view() = default;
            normalized_view(Rng rng)
                    : rng(std::move(rng))
            {}

        private:
            friend struct cursor;

            Rng rng;
        };
    } // namespace detail

    /**
     * .. function:: template <NormalizationForm Form, ForwardRange Rng>\
     *               auto normalize(Rng rng)
     *
     *     Normalizes a range of |code-points| into ``Form``.
     *
     *     :param rng: The range of |code-points| to normalize
     *
     *     :returns: a range of the |code-points| that satisfies the normalization form ``Form``
     */
    namespace fun {
        template <typename Form>
        struct normalize {
            CONCEPT_ASSERT(NormalizationForm<Form>());

            template <typename Rng>
            auto operator()(Rng rng) const {
                return detail::normalized_view<Form, Rng>(rng);
            }
        };
    } // namespace fun
    inline namespace {
        template <typename Form>
        constexpr auto const& normalize = detail::static_const<fun::normalize<Form>>::value;
    }
} // namespace ogonek

#endif // OGONEK_NORMALIZATION_HPP
