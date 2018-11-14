#ifndef GX__BUFFERSTREAM_H
#define GX__BUFFERSTREAM_H

#include <GxGraphics/GxGraphicsTypes.h>

#include <pcx/non_copyable.h>

#include <cstring>

namespace Gx
{

template<typename T> class BufferStream : public pcx::non_copyable
{
public:
    BufferStream(T &v, Graphics::Lock::Flags flags) : v(&v), ptr(static_cast<char*>(v.lock(flags))) { }
    BufferStream(BufferStream &&s) : v(s.v), ptr(v.ptr) { s.v = nullptr; }
    ~BufferStream(){ if(v) v->unlock(); }

    template<typename V> BufferStream &operator<<(const V &value){ std::memcpy(ptr, &value, sizeof(V)); ptr += sizeof(V); return *this; }

private:
    T *v;
    char *ptr;
};

}

#endif // GX__BUFFERSTREAM_H
