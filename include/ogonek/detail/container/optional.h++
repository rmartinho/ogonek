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

#ifndef OGONEK_DETAIL_CONTAINER_OPTIONAL_HPP
#define OGONEK_DETAIL_CONTAINER_OPTIONAL_HPP

#include <ogonek/concepts.h++>
#include <ogonek/types.h++>

#include <cassert>

namespace ogonek {
    template <typename Encoding>
    struct encoded_character;

    namespace detail {
        template <typename T>
        struct optional;

        template <>
        struct optional<code_point> {
        public:
            optional()
            : u(0xFFFFFFFF) {}

            optional(code_point u)
            : u(u) {
                assert(u != 0xFFFFFFFF);
            }

            code_point operator*() const {
                assert(u != 0xFFFFFFFF);
                return u;
            }

            explicit operator bool() const {
                return u != 0xFFFFFFFF;
            }

        private:
            code_point u;
        };

        CONCEPT_ASSERT(Optional<optional<code_point>>());

        template <typename Encoding>
        struct optional<encoded_character<Encoding>> {
        public:
            optional()
            : e() {}

            optional(encoded_character<Encoding> e)
            : e(e) {
                assert(e.size() > 0);
            }

            encoded_character<Encoding> const& operator*() const {
                assert(e.size() > 0);
                return e;
            }

            explicit operator bool() const {
                return e.size() > 0;
            }

        private:
            encoded_character<Encoding> e;
        };

        CONCEPT_ASSERT(Optional<optional<code_point>>());
    } // namespace detail
} // namespace ogonek

#endif //OGONEK_DETAIL_CONTAINER_OPTIONAL_HPP
