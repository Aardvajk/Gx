#ifndef GX_TRANSFORM_H
#define GX_TRANSFORM_H

#include <GxMaths/GxVector.h>
#include <GxMaths/GxQuaternion.h>
#include <GxMaths/GxBlendValue.h>

namespace Gx
{

class Transform
{
public:
    Transform();
    Transform(const Vec3 &position, const Quaternion &rotation);
    Transform(const Vec3 &position, const Vec2 &angle);

    void setPosition(const Vec3 &position);
    void setRotation(const Quaternion &rotation);
    void setAngle(const Vec2 &angle);

    Vec3 position() const;
    Quaternion rotation() const;
    Vec2 angle() const;

private:
    Vec3 pos;
    Quaternion rot;
};

template<> struct Interpolator<Transform>
{
    Transform operator()(const Transform &a, const Transform &b, float t) const;
};

using BlendTransform = BlendValue<Transform>;

}

#endif // GX_TRANSFORM_H
