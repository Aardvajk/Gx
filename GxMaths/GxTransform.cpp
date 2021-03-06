#include "GxMaths/GxTransform.h"

#include "GxMaths/GxMatrix.h"

Gx::Transform::Transform() : pos(0, 0, 0), rot(Quaternion::identity())
{
}

Gx::Transform::Transform(const Vec3 &position, const Quaternion &rotation) : pos(position), rot(rotation)
{
}

Gx::Transform::Transform(const Vec3 &position, const Vec2 &angle) : pos(position), rot(Quaternion::axisRotation(Vec3(angle.y, angle.x, 0)))
{
}

void Gx::Transform::setPosition(const Vec3 &position)
{
    pos = position;
}

void Gx::Transform::setRotation(const Quaternion &rotation)
{
    rot = rotation;
}

void Gx::Transform::setAngle(const Vec2 &angle)
{
    rot = Quaternion::axisRotation(Vec3(angle.y, angle.x, 0));
}

Gx::Vec3 Gx::Transform::position() const
{
    return pos;
}

Gx::Quaternion Gx::Transform::rotation() const
{
    return rot;
}

Gx::Vec2 Gx::Transform::angle() const
{
    return rot.angle();
}

Gx::Transform Gx::Interpolator<Gx::Transform>::operator()(const Transform &a, const Transform &b, float t) const
{
    return Transform(Interpolator<Vec3>()(a.position(), b.position(), t), Interpolator<Quaternion>()(a.rotation(), b.rotation(), t));
}
