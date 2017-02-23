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

// Vector like container backed by a fixed size array (fixed capacity)

#ifndef OGONEK_DETAIL_CONTAINER_PARTIAL_ARRAY_HPP
#define OGONEK_DETAIL_CONTAINER_PARTIAL_ARRAY_HPP

#include <algorithm>
#include <array>
#include <initializer_list>
#include <type_traits>

#include <cstddef>

namespace ogonek {
    namespace detail {
        template <typename T, std::size_t N>
        struct partial_array {
            static_assert(std::is_pod<T>::value, "T must be POD");
        public:
            partial_array() = default;
            partial_array(partial_array const&) = default;
            partial_array(partial_array&&) = default;
            partial_array& operator=(partial_array const&) = default;
            partial_array& operator=(partial_array&&) = default;

            template <typename U>
            partial_array(partial_array<U, N> const& that)
            : partial_array(that.begin(), that.end()) {}

            partial_array(std::size_t size)
            : count(size), array() {}

            partial_array(std::array<T, N> const& array, std::size_t count)
            : partial_array(array.begin(), array.begin() + count) {}

            partial_array(std::initializer_list<T> list)
            : partial_array(list.begin(), list.end()) {}

            template <typename It>
            partial_array(It first, It last)
            : count(last - first), array() {
                std::copy(first, last, array.begin());
            }

            void push_back(T const& item) { array[count++] = item; }
            void clear() { count = 0; }

            using iterator = typename std::array<T, N>::iterator;
            using const_iterator = typename std::array<T, N>::const_iterator;

            iterator begin() { return array.begin(); }
            const_iterator begin() const { return array.begin(); }
            iterator end() { return array.begin() + count; }
            const_iterator end() const { return array.begin() + count; }

            T* data() { return array.data(); }
            T const* data() const { return array.data(); }

            std::size_t size() const { return count; }

            T& operator[](std::ptrdiff_t index) { return array[index]; }
            T const& operator[](std::ptrdiff_t index) const { return array[index]; }

            iterator erase(iterator first) {
                std::copy(std::next(first), end(), first);
                --count;
                return first;
            }

        private:
            std::size_t count = 0;
            std::array<T, N> array;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_CONTAINER_PARTIAL_ARRAY_HPP
