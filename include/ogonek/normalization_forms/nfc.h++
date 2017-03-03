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
#include <ogonek/concepts.h++>
#include <ogonek/normalization_forms/nfd.h++>

namespace ogonek {
    struct nfc : public nfd {
        template <typename Rng,
                  CONCEPT_REQUIRES_(ForwardRangeOf<Rng, code_point>()),
                  CONCEPT_REQUIRES_(OutputRange<Rng, code_point>())>
        static void compose(Rng rng) {
        }
    };
    CONCEPT_ASSERT(NormalizationForm<nfc>());
} // namespace ogonek

#endif // OGONEK_NORMALIZATION_FORMS_NFC_HPP
