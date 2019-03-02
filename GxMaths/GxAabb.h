#ifndef GX_AABB_H
#define GX_AABB_H

#include <GxMaths/GxVector.h>

namespace Gx
{

class Aabb
{
public:
    Aabb();
    Aabb(const Vec3 &min, const Vec3 &max);

    bool intersects(const Aabb &a) const;

    Aabb translated(const Vec3 &v) const;
    Aabb expanded(float margin) const;
    Aabb transformed(const Matrix &m) const;

    Vec3 min;
    Vec3 max;
};

}

#endif // GX_AABB_H
