#ifndef GX_RECT_H
#define GX_RECT_H

#include <GxMaths/GxPoint.h>
#include <GxMaths/GxSize.h>

namespace Gx
{

template<typename T> class BasicRect
{
public:
    BasicRect() = default;
    BasicRect(const BasicPoint<T> &position, const BasicSize<T> &size) : position(position), size(size) { }

    BasicPoint<T> position;
    BasicSize<T> size;
};

class Rect : public BasicRect<int>
{
public:
    using BasicRect::BasicRect;
};

class RectF : public BasicRect<float>
{
public:
    using BasicRect::BasicRect;
};

}

#endif // GXRECT_H
