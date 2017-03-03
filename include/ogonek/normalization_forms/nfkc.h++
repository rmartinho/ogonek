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

#ifndef OGONEK_NORMALIZATION_FORMS_NFKC_HPP
#define OGONEK_NORMALIZATION_FORMS_NFKC_HPP

#include <ogonek/normalization_forms/nfkd.h++>

namespace ogonek {
    struct nfkc : nfkd {};
    CONCEPT_ASSERT(NormalizationForm<nfkc>());
} // namespace ogonek

#endif // OGONEK_NORMALIZATION_FORMS_NFKC_HPP
