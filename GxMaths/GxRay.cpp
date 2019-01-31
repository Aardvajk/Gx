#include "GxMaths/GxRay.h"

#include "GxMaths/GxSize.h"
#include "GxMaths/GxMatrix.h"
#include "GxMaths/GxViewport.h"

#include <cmath>

pcx::optional<float> Gx::Ray::intersectPlane(const Vec3 &p, const Vec3 &n) const
{
    float denom = n.dot(direction);

    if(fabs(denom) > 1e-6)
    {
        Vec3 p0l0 = p - position;
        return p0l0.dot(n) / denom;
    }

    return { };
}

pcx::optional<float> Gx::Ray::intersectsTri(const Vec3 &a, const Vec3 &b, const Vec3 &c) const
{
    float u, t;
    if(D3DXIntersectTri(&a, &b, &c, &position, &direction, &u, &u, &t))
    {
        return t;
    }
    
    return { };
}

pcx::optional<float> Gx::Ray::intersectsTriFacing(const Vec3 &a, const Vec3 &b, const Vec3 &c, const Vec3 &normal) const
{
    if(direction.dot(normal) < 0)
    {
        return intersectsTri(a, b, c);
    }

    return { };
}

pcx::optional<float> Gx::Ray::intersectsSphere(const Vec3 &origin, float radius) const
{
    Vec3 p = position - origin;

    float b = -p.dot(direction);
    float det = (b * b) - p.dot(p) + (radius * radius);

    if(det < 0)
    {
        return { };
    }

    det = sqrt(det);

    float i1 = b - det;
    float i2 = b + det;

    if(i2 < 0)
    {
        return { };
    }

    if(i1 < 0)
    {
        i1 = 0;
    }

    return i1 < i2 ? i1 : i2;
}


Gx::Ray Gx::Ray::compute(const Vec2 &pos, const SizeF &size, const Matrix &view, const Matrix &proj)
{
    Gx::Viewport vp(size);
    auto id = Gx::Matrix::identity();

    Gx::Vec3 p(pos.x, pos.y, 0);
    Gx::Vec3 a = p.unprojected(vp, id, view, proj);

    p.z = 1.0f;
    Gx::Vec3 b = p.unprojected(vp, id, view, proj);

    return Gx::Ray(a, Gx::Vec3(b - a).normalized());
}

Gx::Ray Gx::Ray::transform(const Ray &ray, const Matrix &transform)
{
    return Ray(ray.position.transformedCoord(transform), ray.direction.transformedNormal(transform));
}

