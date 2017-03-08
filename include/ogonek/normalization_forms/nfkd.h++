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

#ifndef OGONEK_NORMALIZATION_FORMS_NFKD_HPP
#define OGONEK_NORMALIZATION_FORMS_NFKD_HPP

#include <ogonek/concepts/normalization.h++>
#include <ogonek/types.h++>
#include <ogonek/ucd.h++>

namespace ogonek {
    struct nfkd {
        template <typename Out,
                  CONCEPT_REQUIRES_(OutputIterator<Out, code_point>())>
        static void decompose_into(code_point u, Out out) {
            if(ucd::get_decomposition_type(u) != ucd::decomposition_type::none) {
                ucd::detail::get_full_decomposition(u, out, false);
            } else {
                *out++ = u;
            }
        }
    };
    CONCEPT_ASSERT(NormalizationForm<nfkd>());
} // namespace ogonek

#endif // OGONEK_NORMALIZATION_FORMS_NFKD_HPP
