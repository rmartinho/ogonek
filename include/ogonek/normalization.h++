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
 * Normalization forms ``<ogonek/normalization.h++>``
 * ==================================================
 */

#ifndef OGONEK_NORMALIZATION_HPP
#define OGONEK_NORMALIZATION_HPP

#include <ogonek/detail/static_const.h++>
#include <ogonek/detail/normalization/decomposed.h++>

#include <vector> // TODO remove

namespace ogonek {
    namespace fun {
        template <typename Form>
        struct normalize {
            template <typename Rng>
            auto operator()(Rng rng) const {
                return detail::decomposed_view<Rng>(rng);
            }
        };
    } // namespace fun
    inline namespace {
        template <typename Form>
        constexpr auto const& normalize = detail::static_const<fun::normalize<Form>>::value;
    }
} // namespace ogonek

#endif // OGONEK_NORMALIZATION_HPP
