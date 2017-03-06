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

// Unicode character database - Word_Break property

#ifndef OGONEK_UCD_WORD_BREAK_HPP
#define OGONEK_UCD_WORD_BREAK_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class word_break {
                cr = 0x1,
                dq = 0x2,
                eb = 0x4,
                ebg = 0x8,
                em = 0x10,
                ex = 0x20,
                extend = 0x40,
                fo = 0x80,
                gaz = 0x100,
                hl = 0x200,
                ka = 0x400,
                le = 0x800,
                lf = 0x1000,
                mb = 0x2000,
                ml = 0x4000,
                mn = 0x8000,
                nl = 0x10000,
                nu = 0x20000,
                ri = 0x40000,
                sq = 0x80000,
                xx = 0x100000,
                zwj = 0x200000,
                double_quote = dq,
                e_base = eb,
                e_base_gaz = ebg,
                e_modifier = em,
                extend_num_let = ex,
                format = fo,
                glue_after_zwj = gaz,
                hebrew_letter = hl,
                katakana = ka,
                aletter = le,
                mid_num_let = mb,
                mid_letter = ml,
                mid_num = mn,
                newline = nl,
                numeric = nu,
                regional_indicator = ri,
                single_quote = sq,
                other = xx,
            };
            struct word_break_properties {
                code_point start;
                word_break value;
            };

            extern OGONEK_PUBLIC word_break_properties const* word_break_data;
            extern OGONEK_PUBLIC std::size_t word_break_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_WORD_BREAK_HPP
