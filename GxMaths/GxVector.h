#ifndef GXVECTOR_H
#define GXVECTOR_H

#include <d3dx9.h>

namespace Gx
{

class Matrix;

class Vec2 : public D3DXVECTOR2
{
public:
    using D3DXVECTOR2::D3DXVECTOR2;

    Vec2() = default;
    Vec2(const D3DXVECTOR2 &v) : D3DXVECTOR2(v) { }

    Vec2 normalized() const { Vec2 v; D3DXVec2Normalize(&v, this); return v; }
    
    Vec2 transformedCoord(const Matrix &v) const;
    Vec2 transformedNormal(const Matrix &v) const;

    Vec2 interpolated(const Vec2 &v, float t) const { return (*this * (1.0f - t)) + (v * t); }
    
    float dot(const Vec2 &v) const { return D3DXVec2Dot(this, &v); }

    float length() const { return D3DXVec2Length(this); }
    float lengthSq() const { return D3DXVec2LengthSq(this); }
};

class Vec3 : public D3DXVECTOR3
{
public:
    using D3DXVECTOR3::D3DXVECTOR3;

    Vec3() = default;
    Vec3(const D3DXVECTOR3 &v) : D3DXVECTOR3(v) { }

    Vec3 normalized() const { Vec3 v; D3DXVec3Normalize(&v, this); return v; }
    Vec3 cross(const Vec3 &v) const;

    Vec3 transformedCoord(const Matrix &v) const;
    Vec3 transformedNormal(const Matrix &v) const;

    Vec3 interpolated(const Vec3 &v, float t) const { return (*this * (1.0f - t)) + (v * t); }

    float dot(const Vec3 &v) const { return D3DXVec3Dot(this, &v); }

    float length() const { return D3DXVec3Length(this); }
    float lengthSq() const { return D3DXVec3LengthSq(this); }
};

class Vec4 : public D3DXVECTOR4
{
public:
    using D3DXVECTOR4::D3DXVECTOR4;

    Vec4() = default;
    Vec4(const D3DXVECTOR4 &v) : D3DXVECTOR4(v) { }

    Vec4 normalized() const { Vec4 v; D3DXVec4Normalize(&v, this); return v; }

    Vec4 transformed(const Matrix &v) const;

    Vec4 interpolated(const Vec4 &v, float t) const { return (*this * (1.0f - t)) + (v * t); }

    float dot(const Vec4 &v) const { return D3DXVec4Dot(this, &v); }

    float length() const { return D3DXVec4Length(this); }
    float lengthSq() const { return D3DXVec4LengthSq(this); }
};

}

#endif // GXVECTOR_H
