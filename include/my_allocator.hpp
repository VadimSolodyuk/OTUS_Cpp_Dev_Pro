#pragma once

#include <cstddef>
#include <memory>
#include <new>

struct deleter {
    void operator()(void* ptr) {
        ::operator delete(ptr);
    }
};

template <class T, std::size_t N = 100 >
struct my_allocator {
    using value_type = T;

    static constexpr std::size_t PoolSize = N;
    int allocated_Size;
    std::shared_ptr<void> pool;

    my_allocator () noexcept = default;  

    template <class U, std::size_t M>
    my_allocator(const my_allocator <U, M>& a) noexcept {
        pool = a.pool;
    }

    my_allocator select_on_container_copy_construction() const { 
        return my_allocator(); 
    }

    T* allocate (std::size_t n) {
        if (pool == nullptr)
            pool = std::shared_ptr<void>(::operator new (sizeof(T) * PoolSize), deleter());
        if(n > (PoolSize - allocated_Size))
            throw std::bad_alloc{};
        auto ptr = (char*)pool.get() + allocated_Size * sizeof(T);        
        allocated_Size += n;
        return reinterpret_cast<T*>(ptr);
    }
    
    void deallocate ([[__maybe_unused__]] T* p, std::size_t n) {
        p = nullptr;
        allocated_Size -= (allocated_Size - n); 
    }

    template< class U >
    struct rebind {
        typedef my_allocator<U, N> other;
    };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;
};

template <class T, std::size_t N, class U, std::size_t M>
constexpr bool operator== (const my_allocator<T, N>& a1, const my_allocator<U, M>& a2) noexcept {
    return a1.pool == a2.pool;
}

template <class T, std::size_t N, class U, std::size_t M>
constexpr bool operator!= (const my_allocator<T, N>& a1, const my_allocator<U, M>& a2) noexcept {
    return a1.pool != a2.pool;
}