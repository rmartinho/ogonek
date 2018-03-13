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

#ifndef OGONEK_SEGMENTATION_SENTENCE_HPP
#define OGONEK_SEGMENTATION_SENTENCE_HPP

#include <ogonek/types.h++>
#include <ogonek/concepts/segmentation.h++>

namespace ogonek {
    struct sentence {
        static bool is_boundary(code_point, code_point) {
            return false;
        }
    };
    CONCEPT_ASSERT(BoundaryCondition<sentence>());
} // namespace ogonek

#endif // OGONEK_SEGMENTATION_SENTENCE_HPP
