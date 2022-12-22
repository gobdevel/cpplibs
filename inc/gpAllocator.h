#pragma once
#include <limits>

namespace GpCpplib {
/**
 * Simple Allocator
 */
template <typename T>
class CustomAllocator {
public:
    // Only Mandatory typedef
    using value_type = T;

    // Optionals typedefs
    using pointer       = T *;
    using const_pointer = const pointer;

    using void_pointer       = void *;
    using const_void_pointer = const void_pointer;

    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    CustomAllocator()  = default;
    ~CustomAllocator() = default;

    template <typename U>
    CustomAllocator(const CustomAllocator<U> &other) {}

    pointer allocate(size_type numObjects) {
        if (numObjects == 0) {
            return nullptr;
        }
        return static_cast<pointer>(operator new(sizeof(T) * numObjects));
    }

    // allocate override for locality of reference
    pointer allocate(size_type numObjects, const_void_pointer hint) {
        allocate(numObjects);
    }

    void deallocate(pointer p, size_type size) {
        operator delete(p);
    }

    size_type max_size() const { return std::numeric_limits<size_type>::max(); }

    // optional
    template <typename U, typename... Args>
    void construct(U *p, Args &&...args) {
        new (p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U *p) {
        p->~U();
    }
};
}  // namespace GpCpplib
