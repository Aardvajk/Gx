#ifndef GX_QUATERNION_H
#define GX_QUATERNION_H

#include <d3dx9.h>

namespace Gx
{

class Vec2;
class Vec3;
class Matrix;

class Quaternion : public D3DXQUATERNION
{
public:
    using D3DXQUATERNION::D3DXQUATERNION;

    Quaternion() = default;
    Quaternion(const D3DXQUATERNION &v) : D3DXQUATERNION(v) { }

    Matrix matrix() const;
    Vec2 angle() const;

    Quaternion rotationBetween(const Vec3 &a, const Vec3 &b) const;
    Quaternion interpolated(const Quaternion &v, float t) const;

    static Quaternion identity();
    static Quaternion axisRotation(const Vec3 &v);
};

}

#endif // GX_QUATERNION_H
