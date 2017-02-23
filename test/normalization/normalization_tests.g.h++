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

// Unicode normalization test data

#ifndef OGONEK_TEST_NORMALIZATION_HPP
#define OGONEK_TEST_NORMALIZATION_HPP

#include "util.h++"

namespace test {
    struct normalization_test {
        u32string input;
        u32string nfc;
        u32string nfd;
        u32string nfkc;
        u32string nfkd;
    };

    extern normalization_test normalization_test_data[18722];
} // namespace test

#endif // OGONEK_TEST_NORMALIZATION_HPP
