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

// This file was automatically generated.

// Unicode character database - Grapheme_Cluster_Break property

#ifndef OGONEK_UCD_GRAPHEME_CLUSTER_BREAK_HPP
#define OGONEK_UCD_GRAPHEME_CLUSTER_BREAK_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class grapheme_cluster_break {
                cn = 0x1,
                cr = 0x2,
                eb = 0x4,
                ebg = 0x8,
                em = 0x10,
                ex = 0x20,
                gaz = 0x40,
                l = 0x80,
                lf = 0x100,
                lv = 0x200,
                lvt = 0x400,
                pp = 0x800,
                ri = 0x1000,
                sm = 0x2000,
                t = 0x4000,
                v = 0x8000,
                xx = 0x10000,
                zwj = 0x20000,
                control = cn,
                e_base = eb,
                e_base_gaz = ebg,
                e_modifier = em,
                extend = ex,
                glue_after_zwj = gaz,
                prepend = pp,
                regional_indicator = ri,
                spacing_mark = sm,
                other = xx,
            };
            struct grapheme_cluster_break_properties {
                code_point start;
                grapheme_cluster_break value;
            };

            extern OGONEK_PUBLIC grapheme_cluster_break_properties const* grapheme_cluster_break_data;
            extern OGONEK_PUBLIC std::size_t grapheme_cluster_break_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_GRAPHEME_CLUSTER_BREAK_HPP
