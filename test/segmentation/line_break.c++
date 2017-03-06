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

// Tests for line breaks

#include <ogonek/segmentation.h++>
#include <ogonek/segmentation/line.h++>

#include <catch.hpp>
#include "util.h++"
#include "segmentation/test_segmentation.h++"

TEST_CASE("official line break tests", "[segmentation][official][lines]") {
    test::test_segmentation_breaks<ogonek::line>();
}