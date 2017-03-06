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

// Tests for the Normalization Form KC

#include <ogonek/normalization_forms/nfkc.h++>

#include <catch.hpp>
#include "util.h++"
#include "normalization/test_normalization.h++"

TEST_CASE("official NFKC tests", "[normalization][official][nfkc]") {
    test::test_normalization_form<ogonek::nfkc>();
}
