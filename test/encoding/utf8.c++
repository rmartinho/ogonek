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

// Tests for the UTF-8 encoding

#include <ogonek/encoding.h++>
#include <ogonek/encodings/utf8.h++>

#include <catch.hpp>
#include "util.h++"
#include "encoding/test_encodings.h++"

#include <range/v3/view/all.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/utility/functional.hpp>

#include <string>

using namespace test::string_literals;

// Based on Markus Kuhn's UTF-8 decoder capability and stress test <http://www.cl.cam.ac.uk/~mgk25/ucs/examples/UTF-8-test.txt>
TEST_CASE("UTF-8 encoding works as expected", "[encoding]") {
    SECTION("Correct") {
        test::test_encoding<ogonek::utf8>(U"\u0000\u007F\u0080\u07FF\u0800\uD7FF\uE000\uFFFF\U00010000\U0010FFFF"_s,
                                         u8"\u0000\u007F\u0080\u07FF\u0800\uD7FF\uE000\uFFFF\U00010000\U0010FFFF"_s);
    }
}
