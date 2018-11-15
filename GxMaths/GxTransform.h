#ifndef GX_TRANSFORM_H
#define GX_TRANSFORM_H

#include <GxMaths/GxVector.h>
#include <GxMaths/GxQuaternion.h>

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

    Transform interpolated(const Transform &v, float t) const;
    void flatVectors(Vec3 &look, Vec3 &right) const;

private:
    Vec3 pos;
    Quaternion rot;
};

}

#endif // GX_TRANSFORM_H