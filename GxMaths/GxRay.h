#ifndef GX_RAY_H
#define GX_RAY_H

#include <GxMaths/GxVector.h>

#include <pcx/optional.h>

namespace Gx
{

class Ray
{
public:
    Ray() = default;
    Ray(const Vec3 &position, const Vec3 &direction) : position(position), direction(direction) { }

    pcx::optional<float> intersectPlane(const Vec3 &p, const Vec3 &n) const;
    pcx::optional<float> intersectsTri(const Vec3 &a, const Vec3 &b, const Vec3 &c) const;
    pcx::optional<float> intersectsTriFacing(const Vec3 &a, const Vec3 &b, const Vec3 &c, const Vec3 &normal) const;
    pcx::optional<float> intersectsSphere(const Vec3 &origin, float radius) const;

    static Ray compute(const Vec2 &position, const Vec2 &size, const Matrix &view, const Matrix &proj);
    static Ray transform(const Ray &ray, const Matrix &transform);
    
    Vec3 position;
    Vec3 direction;
};

}

#endif // GX_RAY_H
