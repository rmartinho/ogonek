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

// Segmentation test utils

#include <ogonek/segmentation.h++>

#include <catch.hpp>
#include "util.h++"
#include "segmentation/segmentation_tests.g.h++"

#include <range/v3/view/all.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/to_container.hpp>

#include <vector>

namespace ogonek {
    struct grapheme_cluster;
    struct word;
    struct sentence;
    struct line;
}

namespace test {
    namespace detail {
        template <typename B>
        struct test_data;
        template <>
        struct test_data<ogonek::grapheme_cluster> {
            static auto& get() { return grapheme_test_data; }
        };
        template <>
        struct test_data<ogonek::word> {
            static auto& get() { return word_test_data; }
        };
        template <>
        struct test_data<ogonek::sentence> {
            static auto& get() { return sentence_test_data; }
        };
        template <>
        struct test_data<ogonek::line> {
            static auto& get() { return line_test_data; }
        };
    } // namespace detail

    template <typename B>
    void test_segmentation() {
        for(auto&& t : detail::test_data<B>::get()) {
            INFO(t.input);
            auto in = ranges::view::all(t.input);
            auto breaks = ogonek::boundaries<B>(in)
                        | ranges::view::transform([&in](auto it) { return int(it - ranges::begin(in)); })
                        | ranges::to_vector;
            breaks.push_back(t.input.size());
            CHECK(breaks == t.breaks);
        }
    }
} // namespace test

