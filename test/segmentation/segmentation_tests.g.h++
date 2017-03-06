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

// Types for segmentation tests

#ifndef OGONEK_TEST_SEGMENTATION_HPP
#define OGONEK_TEST_SEGMENTATION_HPP

#include "util.h++"

#include <vector>

namespace test {
    struct break_test {
        u32string input;
        std::vector<int> breaks;
    };

    extern break_test grapheme_test_data[822];
    extern break_test word_test_data[2057];
    extern break_test sentence_test_data[502];
    extern break_test line_test_data[7312];
} // namespace test

#endif // OGONEK_TEST_SEGMENTATION_HPP
