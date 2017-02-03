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
 * Concepts ``<ogonek/concepts.h++>``
 * ==================================
 */

/**
 * .. todo:: Put the concepts here
 */

#ifndef OGONEK_CONCEPTS_HPP
#define OGONEK_CONCEPTS_HPP

#include <range/v3/utility/concepts.hpp>

namespace ogonek {
    namespace concepts {
        using ranges::concepts::valid_expr;
        using ranges::concepts::models;
        using ranges::concepts::model_of;
        using ranges::concepts::is_true;
        using ranges::concepts::Integral;
    } // namespace ogonek
} // namespace concepts

#endif // OGONEK_CONCEPTS_HPP
