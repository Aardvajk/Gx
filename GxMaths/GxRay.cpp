#include "GxMaths/GxRay.h"

#include "GxMaths/GxMatrix.h"

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

    if(i1 < 0) i1 = 0;

    return i1 < i2 ? i1 : i2;
}


Gx::Ray Gx::Ray::compute(const Vec2 &pos, const Vec2 &size, const Matrix &view, const Matrix &proj)
{
    float w = size.x;
    float h = size.y;

    float sx = pos.x;
    float sy = pos.y;

    Vec3 v;
    v.x = (((2.0f * sx) / w ) - 1) / proj._11;
    v.y = -(((2.0f * sy) / h) - 1) / proj._22;
    v.z =  1.0f;

    Matrix m = view.inverse();

    Ray ray;

    ray.direction.x = v.x*m._11 + v.y*m._21 + v.z*m._31;
    ray.direction.y = v.x*m._12 + v.y*m._22 + v.z*m._32;
    ray.direction.z = v.x*m._13 + v.y*m._23 + v.z*m._33;
    ray.position.x = m._41;
    ray.position.y = m._42;
    ray.position.z = m._43;

    ray.direction = ray.direction.normalized();

    return ray;
}

Gx::Ray Gx::Ray::transform(const Ray &ray, const Matrix &transform)
{
    return Ray(ray.position.transformedCoord(transform), ray.direction.transformedNormal(transform));
}

