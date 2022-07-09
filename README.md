# Floating pointers

A revolutionary standard-ready C++ library

---

Double-precision floats have 53 bits of precision. x86-64 uses a 48-bit virtual address space. The shenanigans here are
destiny.

Basic usage:

```cpp
#include <floating_pointers.hpp>
using based::floating_pointer;

template<typename T>
T sum(floating_pointer<T> array, std::size_t N) {
    T s{};
    for(auto it = array; it != array + N; it++) {
        s += *it;
    }
    return s;
}

void invert_tree(floating_pointer<Node> root) {
    if(root) {
        std::swap(root->left, root->right);
        invert_tree(root->left);
        invert_tree(root->right);
    }
}
```

Reasons to use floating pointers:
- Allows square roots of pointers
- Extends `nullptr` theory with nan pointers, infinity pointers, and negative null pointers

# Api:

## `based::floating_pointer`

```cpp
template<typename T>
class floating_pointer {
public:
    constexpr floating_pointer() = default;
    constexpr floating_pointer(T*);
    constexpr floating_pointer(std::nullptr_t);
    // Conversion
    constexpr operator bool() const;
    constexpr operator T*() const;
    explicit constexpr operator uintptr_t() const;
    explicit constexpr operator intptr_t() const;
    // Member access
    constexpr T& operator*() const;
    constexpr T* operator->() const;
    constexpr T& operator[](std::size_t) const;
    // Comparison
    constexpr bool operator==(floating_pointer) const;
    constexpr bool operator!=(floating_pointer) const;
    constexpr bool operator<(floating_pointer) const;
    constexpr bool operator<=(floating_pointer) const;
    constexpr bool operator>(floating_pointer) const;
    constexpr bool operator>=(floating_pointer) const;
    // Arithmetic
    constexpr floating_pointer& operator++();
    constexpr floating_pointer& operator--();
    constexpr floating_pointer operator++(int);
    constexpr floating_pointer operator--(int);
    template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
    constexpr floating_pointer& operator+=(V);
    template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
    constexpr floating_pointer& operator-=(V);
    template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
    constexpr floating_pointer& operator*=(V);
    template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
    constexpr floating_pointer& operator/=(V);
    template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
    constexpr floating_pointer& operator%=(V);
    template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
    constexpr floating_pointer operator+(V) const;
    template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
    constexpr floating_pointer operator-(V) const;
    template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
    constexpr floating_pointer operator*(V) const;
    template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
    constexpr floating_pointer operator/(V) const;
    template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
    constexpr floating_pointer operator%(V) const;
    // Math
    friend constexpr floating_pointer<T> abs(floating_pointer<T>);
    friend constexpr floating_pointer<T> sqrt(floating_pointer<T>);
    template<typename V, typename std::enable_if<std::is_arithmetic<V>::value, int>::type = 0>
    friend constexpr floating_pointer<T> fmod(floating_pointer<T>, V);
    template<typename U, typename V, typename std::enable_if<
                                                  std::is_arithmetic<U>::value && std::is_arithmetic<V>::value,
                                                  int
                                              >::type = 0>
    friend constexpr floating_pointer<T> fma(floating_pointer<T>, U, V);
    template<typename U, typename V, typename std::enable_if<
                                                  std::is_arithmetic<U>::value && std::is_arithmetic<V>::value,
                                                  int
                                              >::type = 0>
    friend constexpr floating_pointer<T> fma(U, floating_pointer<T>, V);
    template<typename U, typename V, typename std::enable_if<
                                                  std::is_arithmetic<U>::value && std::is_arithmetic<V>::value,
                                                  int
                                              >::type = 0>
    friend constexpr floating_pointer<T> fma(U, V, floating_pointer<T>);
}
```

## `based::inftyptr`

A pointer constant of type `based::inftyptr_t` implicitly convertible to a `floating_pointer<T>` with underlying value
infinity.

## `based::nanptr`

A pointer constant of type `based::nanptr_t` implicitly convertible to a `floating_pointer<T>` with underlying value
NAN.

## `based::negativenullptr`

A pointer constant of type `based::negativenullptr_t` implicitly convertible to a `floating_pointer<T>` with underlying
value -0.

## `based::negativeinfinityptr`

A pointer constant of type `based::negativeinfinityptr_t` implicitly convertible to a `floating_pointer<T>` with
underlying value of negative infinity.

## `based::floating_reference_wrapper`

A container providing a similar interface to `std::reference_wrapper` but utilizing revolutionary
`based::floating_pointer`s.

```cpp
template<typename T>
class floating_reference_wrapper {
    using type = T;
    template<typename U,
             typename std::enable_if<
                 !std::is_same<
                     typename std::remove_cv<typename std::remove_reference<U>::type>::type,
                     floating_reference_wrapper
                 >::value,
                 int
             >::type = 0>
    constexpr floating_reference_wrapper(U&&);
    constexpr operator T&() const;
    constexpr T& get() const;
};

template<typename T> floating_reference_wrapper(T&) -> floating_reference_wrapper<T>;
```
