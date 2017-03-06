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

// Normalization test utils

#include <ogonek/normalization.h++>

#include <catch.hpp>
#include "util.h++"
#include "normalization/normalization_tests.g.h++"

#include <range/v3/view/all.hpp>
#include <range/v3/to_container.hpp>

namespace ogonek {
    struct nfd;
    struct nfc;
    struct nfkd;
    struct nfkc;
}

namespace test {
    namespace detail {
        template <typename n>
        struct expected_result;
        template <>
        struct expected_result<ogonek::nfd> {
            template <typename T>
            static auto get(T t) { return t.nfd; }
        };
        template <>
        struct expected_result<ogonek::nfc> {
            template <typename T>
            static auto get(T t) { return t.nfc; }
        };
        template <>
        struct expected_result<ogonek::nfkd> {
            template <typename T>
            static auto get(T t) { return t.nfkd; }
        };
        template <>
        struct expected_result<ogonek::nfkc> {
            template <typename T>
            static auto get(T t) { return t.nfkc; }
        };
    } // namespace detail

    template <typename N>
    void test_normalization_form() {
        CONCEPT_ASSERT(ogonek::NormalizationForm<N>());

        for(auto&& t : test::normalization_test_data) {
            INFO(t.input);
            auto str = ogonek::normalize<N>(ranges::view::all(t.input))
                     | ranges::to_<test::u32string>();
            CHECK(str == detail::expected_result<N>::get(t));
        }
    }
} // namespace test
