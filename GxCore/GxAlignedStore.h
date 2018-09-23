#ifndef GXALIGNEDSTORE_H
#define GXALIGNEDSTORE_H

#include <type_traits>
#include <utility>
#include <memory>

namespace Gx
{

template<std::size_t N> class AlignedStore
{
public:
    template<typename T> void alloc(){ static_assert(N >= sizeof(T), ""); new(&t) T(); }
    template<typename T, typename... Args> void alloc(Args&&... args){ static_assert(N >= sizeof(T), ""); new(&t) T(std::forward<Args>(args)...); }

    template<typename T> T &get(){ return *(reinterpret_cast<T*>(&t)); }
    template<typename T> const T &get() const { return *(reinterpret_cast<const T*>(&t)); }

private:
    typename std::aligned_storage<N>::type t;
};

}

#endif // GXALIGNEDSTORE_H
