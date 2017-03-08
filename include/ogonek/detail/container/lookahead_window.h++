// Ogonek
//
// Written in 2017 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Window of lookaheads

#ifndef OGONEK_DETAIL_CONTAINER_LOOKAHEAD_WINDOW_HPP
#define OGONEK_DETAIL_CONTAINER_LOOKAHEAD_WINDOW_HPP

#include <ogonek/concepts/core.h++>

#include <algorithm>
#include <iterator>
#include <array>
#include <type_traits>

#include <cstddef>

namespace ogonek {
    namespace detail {
        template <typename It, int Before, int After>
        struct lookahead_window {
            using value_type = typename std::iterator_traits<It>::value_type;
            static_assert(std::is_integral<value_type>::value, "value_type must be integral");
        public:
            CONCEPT_ASSERT(ForwardIterator<It>());

            lookahead_window(It first, It last)
            : reader(first), last(last) {
                std::fill(data.begin(), data.end(), -1);
                std::fill(positions.begin(), positions.end(), last);
                for(auto i = 0; i <= After; ++i) {
                    scroll();
                    read_next();
                }
                advance();
            }

            void advance() { skip(-Before); }
            void skip(int limit) {
                scroll(limit);
                read_next();
            }
            bool exhausted() const {
                return positions[0] == last;
            }

            value_type operator[](int n) const {
                return data[Before + n];
            }

            It position() const {
                return positions[0];
            }

        private:
            void scroll(int limit = -Before) {
                for(auto i = limit; i < After; ++i) {
                    data[Before + i] = data[Before + i + 1];
                }
                for(auto i = std::max(limit, 0); i < After; ++i) {
                    positions[i] = positions[i + 1];
                }
            }

            void read_next() {
                positions.back() = reader;
                if(reader == last) {
                    data.back() = -1;
                } else {
                    data.back() = *reader++;
                }
            }

            std::array<value_type, Before + 1 + After> data;
            std::array<It, 1 + After> positions;
            It reader, last;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_CONTAINER_LOOKAHEAD_WINDOW_HPP
