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
 * Segmentation
 * =============
 */

#ifndef OGONEK_SEGMENTATION_HPP
#define OGONEK_SEGMENTATION_HPP

namespace ogonek {
    template <typename Break, typename Rng>
    Rng breaks(Rng rng) { return rng; }
} // namespace ogonek

#endif // OGONEK_SEGMENTATION_HPP
