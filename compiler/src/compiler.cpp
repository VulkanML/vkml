#include <mutex>
#include <numeric>
#include "../include/compiler.h"


template<typename T, size_t N>
struct MemRefDescriptor {
    T* allocated;
    T* aligned;
    int64_t offsest;
    int64_t sizes[N];
    int64_t strides[N];
};

