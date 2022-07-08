#ifndef FLOATING_POINTERS_HPP
#define FLOATING_POINTERS_HPP

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace based {
    static_assert(std::numeric_limits<double>::is_iec559);

    struct inftyptr_t {};
    struct nanptr_t {};
    struct negativenullptr_t {};
    struct negativeinftyptr_t {};

    static constexpr inftyptr_t inftyptr;
    static constexpr nanptr_t nanptr;
    static constexpr negativenullptr_t negativenullptr;
    static constexpr negativeinftyptr_t negativeinftyptr;

    template<typename T>
    class floating_pointer {
        double _ptr;
        static constexpr std::size_t unit = sizeof(T);
        constexpr floating_pointer(double ptr) : _ptr(ptr) {}
    public:
        constexpr floating_pointer() = default;
        constexpr floating_pointer(T* ptr) : _ptr(uintptr_t(ptr)) {}
        constexpr floating_pointer(std::nullptr_t) : _ptr(0) {}
        constexpr floating_pointer(inftyptr_t) : _ptr(INFINITY) {}
        constexpr floating_pointer(nanptr_t) : _ptr(NAN) {}
        constexpr floating_pointer(negativenullptr_t) : _ptr(-0) {}
        constexpr floating_pointer(negativeinftyptr_t) : _ptr(-INFINITY) {}
        // Conversion
        constexpr operator bool() const {
            return _ptr;
        }
        constexpr operator T*() const {
            return (T*)uintptr_t(_ptr);
        }
        explicit constexpr operator uintptr_t() const {
            return uintptr_t(_ptr);
        }
        explicit constexpr operator intptr_t() const {
            return intptr_t(_ptr);
        }
        // Member access
        constexpr T& operator*() const {
            return *(T*)uintptr_t(_ptr);
        }
        constexpr T* operator->() const {
            return (T*)uintptr_t(_ptr);
        }
        constexpr T& operator[](std::size_t i) const {
            return ((T*)uintptr_t(_ptr))[i];
        }
        // Comparison
        constexpr bool operator==(floating_pointer other) const {
            return _ptr == other._ptr;
        }
        constexpr bool operator!=(floating_pointer other) const {
            return _ptr != other._ptr;
        }
        constexpr bool operator<(floating_pointer other) const {
            return _ptr < other._ptr;
        }
        constexpr bool operator<=(floating_pointer other) const {
            return _ptr <= other._ptr;
        }
        constexpr bool operator>(floating_pointer other) const {
            return _ptr > other._ptr;
        }
        constexpr bool operator>=(floating_pointer other) const {
            return _ptr >= other._ptr;
        }
        // Arithmetic
        constexpr floating_pointer& operator++() {
            _ptr += unit;
            return *this;
        }
        constexpr floating_pointer& operator--() {
            _ptr -= unit;
            return *this;
        }
        constexpr floating_pointer operator++(int) {
            floating_pointer copy = *this;
            _ptr += unit;
            return copy;
        }
        constexpr floating_pointer operator--(int) {
            floating_pointer copy = *this;
            _ptr -= unit;
            return copy;
        }
        template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
        constexpr floating_pointer& operator+=(V v) {
            _ptr += v * unit;
            return *this;
        }
        template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
        constexpr floating_pointer& operator-=(V v) {
            _ptr -= v * unit;
            return *this;
        }
        template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
        constexpr floating_pointer operator+(V v) const {
            return _ptr + v * unit;
        }
        template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
        constexpr floating_pointer operator-(V v) const {
            return _ptr - v * unit;
        }
        // Math
        friend constexpr floating_pointer<T> abs(floating_pointer<T> ptr) {
            return {std::abs(ptr._ptr)};
        }
        friend constexpr floating_pointer<T> sqrt(floating_pointer<T> ptr) {
            return {std::sqrt(ptr._ptr)};
        }
    };
}

#endif
