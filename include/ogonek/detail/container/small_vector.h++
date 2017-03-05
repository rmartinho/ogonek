// Ogonek
//
// Written in 2017 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copylarge and related
// and neighboring larges to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Vector like container with small storage optimization

#ifndef OGONEK_DETAIL_CONTAINER_SMALL_VECTOR_HPP
#define OGONEK_DETAIL_CONTAINER_SMALL_VECTOR_HPP

#include <ogonek/detail/container/partial_array.h++>
#include <ogonek/detail/container/either.h++>

#include <algorithm>
#include <vector>
#include <initializer_list>
#include <iterator>
#include <type_traits>

#include <cstddef>

namespace ogonek {
    namespace detail {
        template <typename T, std::size_t N>
        struct small_vector {
            static_assert(std::is_pod<T>::value, "T must be POD");
        public:
            using value_type = T;

            small_vector()
            : storage(make_if(true)) {}

            template <typename U, std::size_t M>
            small_vector(small_vector<U, M> const& that)
            : small_vector(that.begin(), that.end()) {}

            small_vector(std::initializer_list<T> list)
            : small_vector(list.begin(), list.end()) {}

            template <typename It>
            small_vector(It first, It last)
            : storage(make_if(last - first <= N, first, last)) {}

            void push_back(T const& item) {
                if(is_small() && as_small().size() == N) {
                    grow();
                }

                if(is_small()) {
                    as_small().push_back(item);
                } else {
                    as_large().push_back(item);
                }
            }
            void clear() {
                if(is_small()) {
                    as_small().clear();
                } else {
                    as_large().clear();
                }
            }

            using iterator = T*;
            using const_iterator = T const*;

            iterator begin() { return data(); }
            const_iterator begin() const { return data(); }
            iterator end() { return data() + size(); }
            const_iterator end() const { return data() + size(); }

            T* data() {
                if(is_small()) {
                    return as_small().data();
                } else {
                    return as_large().data();
                }
            }
            T const* data() const {
                if(is_small()) {
                    return as_small().data();
                } else {
                    return as_large().data();
                }
            }

            std::size_t size() const {
                if(is_small()) {
                    return as_small().size();
                } else {
                    return as_large().size();
                }
            }

            T& operator[](std::ptrdiff_t index) { return data()[index]; }
            T const& operator[](std::ptrdiff_t index) const { return data()[index]; }

            iterator erase(iterator first, iterator last) {
                auto first_idx = std::distance(begin(), first);
                auto last_idx = std::distance(begin(), last);
                if(is_small()) {
                    return &*as_small().erase(as_small().begin() + first_idx, as_small().begin() + last_idx);
                } else {
                    return &*as_large().erase(as_large().begin() + first_idx, as_large().begin() + last_idx);
                }
            }

        private:
            using storage_t = either<partial_array<T, N>, std::vector<T>>;

            bool is_small() const { return storage.is_left(); }
            bool is_large() const { return storage.is_right(); }
            decltype(auto) as_small() { return storage.as_left(); }
            decltype(auto) as_small() const { return storage.as_left(); }
            decltype(auto) as_large() { return storage.as_right(); }
            decltype(auto) as_large() const { return storage.as_right(); }
            template <typename... Args>
            storage_t make_if(bool condition, Args&&... args) {
                if(condition) {
                    return storage_t::make_left(std::forward<Args>(args)...);
                } else {
                    return storage_t::make_right(std::forward<Args>(args)...);
                }
            }

            void grow() {
                assert(is_small());
                auto copy(as_small());
                storage.place_right(copy.begin(), copy.end());
            }

            storage_t storage;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_CONTAINER_SMALL_VECTOR_HPP
