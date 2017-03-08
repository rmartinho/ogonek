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

// Simple internal variant<T, U> implementation for our own types

#ifndef OGONEK_DETAIL_CONTAINER_EITHER_HPP
#define OGONEK_DETAIL_CONTAINER_EITHER_HPP

#include <type_traits>

#include <cstddef>
#include <cassert>

namespace ogonek {
    namespace detail {
        template <typename T, typename U>
        struct either {
        public:
            template <typename... Args>
            static either<T, U> make_left(Args&&... args) {
                return { std::integral_constant<int, 0>{}, std::forward<Args>(args)... };
            }
            template <typename... Args>
            static either<T, U> make_right(Args&&... args) {
                return { std::integral_constant<int, 1>{}, std::forward<Args>(args)... };
            }

            either(either<T, U> const& that) {
                copy(that);
            }

            either(either<T, U>&& that) {
                move(std::move(that));
            }

            ~either() {
                destroy();
            }

            either<T, U>& operator=(either<T, U> const& that) {
                if(stores_left == that.stores_left) {
                    copy_assign(that);
                } else {
                    // WARNING: not exception safe
                    destroy();
                    copy(that);
                }
                return *this;
            }

            either<T, U>& operator=(either<T, U>&& that) {
                if(stores_left == that.stores_left) {
                    move_assign(std::move(that));
                } else {
                    // WARNING: not exception safe
                    destroy();
                    move(std::move(that));
                }
                return *this;
            }

            template <typename... Args>
            either<T, U>& place_left(Args&&... args) {
                // WARNING: not exception safe
                destroy();
                place<T>(std::forward<Args>(args)...);
                return *this;
            }
            template <typename... Args>
            either<T, U>& place_right(Args&&... args) {
                // WARNING: not exception safe
                destroy();
                place<U>(std::forward<Args>(args)...);
                return *this;
            }

            bool is_left() const { return stores_left; }
            bool is_right() const { return !stores_left; }

            T& as_left() { return as<T>(); }
            T const& as_left() const { return as<T>(); }
            U& as_right() { return as<U>(); }
            U const& as_right() const { return as<U>(); }

        private:
            template <int N, typename... Args>
            either(std::integral_constant<int, N>, Args&&... args) {
                place<std::conditional_t<N == 0, T, U>>(std::forward<Args>(args)...);
            }

            static constexpr std::size_t max(std::size_t a, std::size_t b) {
                return a > b? a : b;
            }

            template <typename TU, typename... Args>
            void place(Args&&... args) {
                ::new(&storage) TU(std::forward<Args>(args)...);
                stores_left = std::is_same<TU, T>();
            }

            void copy(either<T, U> const& that) {
                if(that.stores_left) {
                    place<T>(that.as_left());
                } else {
                    place<U>(that.as_right());
                }
            }
            void move(either<T, U>&& that) {
                if(that.stores_left) {
                    place<T>(std::move(that.as_left()));
                } else {
                    place<U>(std::move(that.as_right()));
                }
            }
            void copy_assign(either<T, U> const& that) {
                if(stores_left) {
                    as_left() = that.as_left();
                } else {
                    as_right() = that.as_right();
                }
            }
            void move_assign(either<T, U> const& that) {
                if(stores_left) {
                    as_left() = std::move(that.as_left());
                } else {
                    as_right() = std::move(that.as_right());
                }
            }
            void destroy() {
                if(stores_left) {
                    as_left().~T();
                } else {
                    as_right().~U();
                }
            }

            template <typename TU>
            TU& as() { // UNSAFE
                return *reinterpret_cast<TU*>(&storage);
            }
            template <typename TU>
            TU const& as() const { // UNSAFE
                return *reinterpret_cast<TU const*>(&storage);
            }

            using storage_t = std::aligned_storage_t<max(sizeof(T), sizeof(U)), max(alignof(T), alignof(U))>;
            storage_t storage;
            bool stores_left;
        };
    } // namespace detail
} // namespace ogonek

#endif //OGONEK_DETAIL_CONTAINER_OPTIONAL_HPP

