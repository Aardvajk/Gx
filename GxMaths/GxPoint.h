#ifndef GX_POINT_H
#define GX_POINT_H

namespace Gx
{

template<typename T> class BasicPoint
{
public:
    BasicPoint() : x(T()), y(T()) { }
    BasicPoint(T x, T y) : x(x), y(y) { }

    T x;
    T y;
};

class Point : public BasicPoint<int>
{
public:
    using BasicPoint::BasicPoint;
};

class PointF : public BasicPoint<float>
{
public:
    using BasicPoint::BasicPoint;
    PointF(const Point &p) : BasicPoint(static_cast<float>(p.x), static_cast<float>(p.y)) { }
};

}

#endif // GX_SIZE_H
