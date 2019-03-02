#include <GxMaths/GxAabb.h>

Gx::Aabb::Aabb()
{
}

Gx::Aabb::Aabb(const Vec3 &min, const Vec3 &max) : min(min), max(max)
{
}

bool Gx::Aabb::intersects(const Aabb &a) const
{
    return !(max.x < a.min.x || min.x > a.max.x || max.y < a.min.y || min.y > a.max.y || max.z < a.min.z || min.z > a.max.z);
}

Gx::Aabb Gx::Aabb::translated(const Vec3 &v) const
{
    Aabb a = *this;

    a.min += v;
    a.max += v;

    return a;
}

Gx::Aabb Gx::Aabb::expanded(float margin) const
{
    Aabb a = *this;

    a.min -= Vec3(margin, margin, margin);
    a.max += Vec3(margin, margin, margin);

    return a;
}

Gx::Aabb Gx::Aabb::transformed(const Matrix &m) const
{
    Aabb a = *this;

    a.min = a.min.transformedCoord(m);
    a.max = a.max.transformedCoord(m);

    return a;
}
