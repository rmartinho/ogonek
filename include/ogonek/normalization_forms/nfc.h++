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

#ifndef OGONEK_NORMALIZATION_FORMS_NFC_HPP
#define OGONEK_NORMALIZATION_FORMS_NFC_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts/normalization.h++>
#include <ogonek/ucd.h++>
#include <ogonek/normalization_forms/nfd.h++>

#include <range/v3/iterator_range.hpp>

namespace ogonek {
    struct nfc : private nfd {
        using nfd::decompose_into;

        template <typename Rng,
                  CONCEPT_REQUIRES_(ForwardRangeOf<code_point, Rng>()), // TODO actually requires bidi-ranges :|
                  CONCEPT_REQUIRES_(OutputRange<Rng, code_point>())>
        static auto compose(Rng rng) {
            constexpr auto no_last_ccc = -1;

            auto is_blocked = [](code_point u, int last_ccc) {
                return last_ccc != no_last_ccc && (last_ccc == 0 || last_ccc >= ucd::get_canonical_combining_class(u));
            };
            auto begin = ranges::begin(rng);
            auto end = ranges::end(rng);
            for(auto l = begin; l != end; ++l) {
                if(ucd::is_excluded_from_composition(*l) || !ucd::detail::can_compose(*l)) {
                    continue;
                }

                auto last_ccc = no_last_ccc;
                for(auto r = std::next(l); r != end; ) {
                    if(!is_blocked(*r, last_ccc) && ucd::detail::can_compose(*l, *r)) {
                        *l = ucd::detail::compose(*l, *r);
                        std::copy(std::next(r), end, r); // TODO optimize
                        --end;
                    } else {
                        last_ccc = ucd::get_canonical_combining_class(*r);
                        ++r;
                    }
                }
            }
            return end;
        }
    };
    CONCEPT_ASSERT(NormalizationForm<nfc>());
} // namespace ogonek

#endif // OGONEK_NORMALIZATION_FORMS_NFC_HPP
