// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Encode ranges

#ifndef OGONEK_ENCODE_HPP
#define OGONEK_ENCODE_HPP

#include "types.h++"
#include "concepts.h++"

#include <range/v3/view_adaptor.hpp>

#include <iostream>
#include <vector>
#include <type_traits>

#include <cstddef>

namespace ogonek {
    namespace concepts {
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

            template<typename T>
            auto requires_(T&& t) -> decltype(
                concepts::valid_expr(
                    concepts::model_of<concepts::Integral, code_unit_t<T>>(),
                    concepts::is_true(max_width_gt_zero_t<T>{}),
                    encode_one<T>(code_point(), std::declval<state_t<T>&>())
                ));
        };
    } // namespace concepts

    //! Concept that represents encoding forms.
    template <typename T>
    using EncodingForm = concepts::models<concepts::EncodingForm, T>;

    //! Gets the code unit type for an encoding.
    template <typename Encoding>
    using code_unit_t = typename concepts::EncodingForm::code_unit_t<Encoding>;

    //! Gets the state type for an encoding. Stateless encodings have empty state types.
    template <typename Encoding>
    using encoding_state_t = typename concepts::EncodingForm::state_t<Encoding>;

    //! Tests whether an encoding is stateless.
    template <typename Encoding>
    using is_stateless = std::is_empty<encoding_state_t<Encoding>>;

    //! Tests whether an encoding is stateless.
    template <typename Encoding>
    constexpr auto is_stateless_v = is_stateless<Encoding>::value;

    //! Encodes one code point.
    //!
    //! :param u: the code point
    //!
    //! :param state: the current state; modified after encoding ``u``
    //!
    //! :return: the code units that encode ``u``
    template <typename Encoding>
    auto encode_one(code_point u, encoding_state_t<Encoding>& state) {
        return concepts::EncodingForm::encode_one<Encoding>(u, state);
    }

    namespace detail {
        template <typename Encoding, typename Rng>
        struct encoded_view
        : ranges::view_adaptor<
            encoded_view<Encoding, Rng>,
            Rng,
            ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value> {
        private:
            using base_type = ranges::view_adaptor<
                encoded_view<Encoding, Rng>,
                Rng,
                ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value>;

            CONCEPT_ASSERT(ranges::Range<Rng>());
            CONCEPT_ASSERT(EncodingForm<Encoding>());

            friend ranges::range_access;

            struct adaptor : public ranges::adaptor_base {
            public:
                typename Encoding::code_unit get(ranges::range_iterator_t<Rng> it) const {
                    if(position < 0) {
                        encoded = encode_one<Encoding>(*it, state);
                        position = 0;
                    }
                    return encoded[position];
                }
                void next(ranges::range_iterator_t<Rng>& it) {
                    ++position;
                    if(position == static_cast<ptrdiff_t>(encoded.size())) {
                        ++it;
                        position = -1;
                    }
                }
                bool equal(ranges::range_iterator_t<Rng> it0, ranges::range_iterator_t<Rng> it1, adaptor const & other) const {
                    return it0 == it1 && position == other.position;
                }

            private:
                mutable std::vector<typename Encoding::code_unit> encoded;
                mutable std::ptrdiff_t position = -1;
                mutable encoding_state_t<Encoding> state {};
            };

            adaptor begin_adaptor() const {
                return {};
            }

        public:
            encoded_view() = default;
            explicit encoded_view(Rng rng)
            : base_type(std::move(rng))
            {}
        };
    } // namespace detail

    /**
     * .. function:: template<EncodingForm Encoding, ranges::Range Rng>\
     *               ranges::Range encode(Rng rng)
     *
     *      :returns: a range of the code units that encode the code points in ``rng``
     *      :validation: as performed by the encoding form
     */
    template <typename Encoding, typename Rng,
              CONCEPT_REQUIRES_(ranges::Range<Rng>() && EncodingForm<Encoding>())>
    auto encode(Rng rng) {
        return detail::encoded_view<Encoding, Rng>(std::move(rng));
    }
} // namespace ogonek


#endif // OGONEK_ENCODE_HPP

