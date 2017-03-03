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

#ifndef OGONEK_NORMALIZATION_FORMS_NFD_HPP
#define OGONEK_NORMALIZATION_FORMS_NFD_HPP

#include <ogonek/concepts.h++>
#include <ogonek/types.h++>
#include <ogonek/ucd.h++>

namespace ogonek {
    struct nfd {
        template <typename Out,
                  CONCEPT_REQUIRES_(OutputIterator<Out, code_point>())>
        static void decompose_into(code_point u, Out out) {
            if(ucd::get_decomposition_type(u) == ucd::decomposition_type::canonical) {
                // TODO internals that push_back directly?
                auto&& str = ucd::get_full_decomposition(u);
                std::copy(str.begin(), str.end(), out);
            } else {
                *out++ = u;
            }
        }
        // TODO compose
    };
    CONCEPT_ASSERT(NormalizationForm<nfd>());
} // namespace ogonek

#endif // OGONEK_NORMALIZATION_FORMS_NFD_HPP
