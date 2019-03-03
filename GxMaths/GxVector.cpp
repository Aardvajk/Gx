#include "GxMaths/GxVector.h"

#include "GxMaths/GxMatrix.h"
#include "GxMaths/GxViewport.h"

Gx::Vec2 Gx::Vec2::normalized() const
{
    Vec2 v;
    D3DXVec2Normalize(&v, this);

    return v;
}

Gx::Vec2 Gx::Vec2::transformedCoord(const Matrix &v) const
{
    Vec2 r;
    D3DXVec2TransformCoord(&r, this, &v);

    return r;
}

Gx::Vec2 Gx::Vec2::transformedNormal(const Matrix &v) const
{
    Vec2 r;
    D3DXVec2TransformNormal(&r, this, &v);

    return r;
}

Gx::Vec2 Gx::Vec2::interpolated(const Vec2 &v, float t) const
{
    return (*this * (1.0f - t)) + (v * t);
}

float Gx::Vec2::dot(const Vec2 &v) const
{
    return D3DXVec2Dot(this, &v);
}

float Gx::Vec2::length() const
{
    return D3DXVec2Length(this);
}

float Gx::Vec2::lengthSq() const
{
    return D3DXVec2LengthSq(this);
}

Gx::Vec3 Gx::Vec3::normalized() const
{
    Vec3 v;
    D3DXVec3Normalize(&v, this);

    return v;
}

Gx::Vec3 Gx::Vec3::cross(const Gx::Vec3 &v) const
{
    Vec3 r;
    D3DXVec3Cross(&r, this, &v);
    
    return r;
}

Gx::Vec3 Gx::Vec3::transformedCoord(const Matrix &v) const
{
    Vec3 r;
    D3DXVec3TransformCoord(&r, this, &v);

    return r;
}

Gx::Vec3 Gx::Vec3::transformedNormal(const Matrix &v) const
{
    Vec3 r;
    D3DXVec3TransformNormal(&r, this, &v);

    return r;
}

Gx::Vec3 Gx::Vec3::interpolated(const Vec3 &v, float t) const
{
    return (*this * (1.0f - t)) + (v * t);
}

Gx::Vec3 Gx::Vec3::unprojected(const Viewport &vp, const Matrix &world, const Matrix &view, const Matrix &proj) const
{
    Gx::Vec3 r;
    D3DXVec3Unproject(&r, this, &vp, &proj, &view, &world);

    return r;
}

Gx::Vec3 Gx::Vec3::reflected(const Vec3 &normal) const
{
    return *this - (2.0f * this->dot(normal)) * normal;
}

Gx::Vec3 Gx::Vec3::parallel(const Vec3 &normal) const
{
    return normal * this->dot(normal);
}

Gx::Vec3 Gx::Vec3::perpendicular(const Vec3 &normal) const
{
    return *this - this->parallel(normal);
}

float Gx::Vec3::dot(const Vec3 &v) const
{
    return D3DXVec3Dot(this, &v);
}

float Gx::Vec3::length() const
{
    return D3DXVec3Length(this);
}

float Gx::Vec3::lengthSq() const
{
    return D3DXVec3LengthSq(this);
}

Gx::Vec4 Gx::Vec4::normalized() const
{
    Vec4 v;
    D3DXVec4Normalize(&v, this);

    return v;
}

Gx::Vec4 Gx::Vec4::transformed(const Gx::Matrix &v) const
{
    Vec4 r;
    D3DXVec4Transform(&r, this, &v);
    
    return r;
}

Gx::Vec4 Gx::Vec4::interpolated(const Vec4 &v, float t) const
{
    return (*this * (1.0f - t)) + (v * t);
}

float Gx::Vec4::dot(const Vec4 &v) const
{
    return D3DXVec4Dot(this, &v);
}

float Gx::Vec4::length() const
{
    return D3DXVec4Length(this);
}

float Gx::Vec4::lengthSq() const
{
    return D3DXVec4LengthSq(this);
}
