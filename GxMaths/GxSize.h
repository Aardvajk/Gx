#ifndef GX_SIZE_H
#define GX_SIZE_H

namespace Gx
{

template<typename T> class BasicSize
{
public:
    BasicSize() : width(T()), height(T()) { }
    BasicSize(T width, T height) : width(width), height(height) { }

    T width;
    T height;
};

class Size : public BasicSize<unsigned>
{
public:
    using BasicSize::BasicSize;
};

class SizeF : public BasicSize<float>
{
public:
    using BasicSize::BasicSize;
};

}

#endif // GX_SIZE_H
