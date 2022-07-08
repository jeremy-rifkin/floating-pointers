# Floating pointers

A revolutionary standard-ready C++ library

---

Double-precision floats have 53 bits of precision. x86-64 uses a 48-bit virtual address space. The shenanigans here are
destiny.

Basic usage:

```
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
