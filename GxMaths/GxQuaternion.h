#ifndef GX_QUATERNION_H
#define GX_QUATERNION_H

#include <GxMaths/GxBlendValue.h>

#include <pcx/datastream.h>

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

    Quaternion interpolated(const Quaternion &v, float t) const;

    static Quaternion identity();
    static Quaternion axisRotation(const Vec3 &v);
    static Quaternion rotationBetween(const Vec3 &a, const Vec3 &b);
};

template<> struct Interpolator<Quaternion>
{
    Quaternion operator()(const Quaternion &a, const Quaternion &b, float t) const;
};

using BlendQuaternion = BlendValue<Quaternion>;

}

inline pcx::data_istream &operator>>(pcx::data_istream &ds, Gx::Quaternion &v){ return ds >> v.x >> v.y >> v.z >> v.w; }
inline pcx::data_ostream &operator<<(pcx::data_ostream &ds, const Gx::Quaternion &v){ return ds << v.x << v.y << v.z << v.w; }

#endif // GX_QUATERNION_H
