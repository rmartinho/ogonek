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

#include <ogonek/normalization.h++>
#include <ogonek/normalization_forms/nfkc.h++>

#include <catch.hpp>
#include "util.h++"
#include "normalization/normalization_tests.g.h++"

#include <range/v3/view/all.hpp>
#include <range/v3/to_container.hpp>

using namespace test::string_literals;

TEST_CASE("official NKFC tests", "[normalization][official][nfkc]") {
    for(auto&& t : test::normalization_test_data) {
        INFO(t.input);
        auto str = ogonek::normalize<ogonek::nfkc>(ranges::view::all(t.input))
                 | ranges::to_<test::u32string>();
        CHECK(str == t.nfkc);
    }
}
