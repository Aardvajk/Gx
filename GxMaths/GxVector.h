#ifndef GX_VECTOR_H
#define GX_VECTOR_H

#include <GxMaths/GxBlendValue.h>

#include <d3dx9.h>

namespace Gx
{

class Matrix;
class Viewport;

class Vec2 : public D3DXVECTOR2
{
public:
    using D3DXVECTOR2::D3DXVECTOR2;

    Vec2() = default;
    Vec2(const D3DXVECTOR2 &v) : D3DXVECTOR2(v) { }

    Vec2 normalized() const;

    Vec2 transformedCoord(const Matrix &v) const;
    Vec2 transformedNormal(const Matrix &v) const;

    Vec2 interpolated(const Vec2 &v, float t) const;
    
    float dot(const Vec2 &v) const;

    float length() const;
    float lengthSq() const;
};

using BlendVec2 = BlendValue<Vec2>;

class Vec3 : public D3DXVECTOR3
{
public:
    using D3DXVECTOR3::D3DXVECTOR3;

    Vec3() = default;
    Vec3(const D3DXVECTOR3 &v) : D3DXVECTOR3(v) { }

    Vec3 normalized() const;
    Vec3 cross(const Vec3 &v) const;

    Vec3 transformedCoord(const Matrix &v) const;
    Vec3 transformedNormal(const Matrix &v) const;

    Vec3 interpolated(const Vec3 &v, float t) const;
    Vec3 unprojected(const Viewport &vp, const Matrix &world, const Matrix &view, const Matrix &proj) const;

    Vec3 reflected(const Vec3 &normal) const;
    Vec3 parallel(const Vec3 &normal) const;
    Vec3 perpendicular(const Vec3 &normal) const;

    float dot(const Vec3 &v) const;

    float length() const;
    float lengthSq() const;
};

using BlendVec3 = BlendValue<Vec3>;

class Vec4 : public D3DXVECTOR4
{
public:
    using D3DXVECTOR4::D3DXVECTOR4;

    Vec4() = default;
    Vec4(const D3DXVECTOR4 &v) : D3DXVECTOR4(v) { }

    Vec4 normalized() const;

    Vec4 transformed(const Matrix &v) const;

    Vec4 interpolated(const Vec4 &v, float t) const;

    float dot(const Vec4 &v) const;

    float length() const;
    float lengthSq() const;
};

using BlendVec4 = BlendValue<Vec4>;

}

#endif // GX_VECTOR_H
