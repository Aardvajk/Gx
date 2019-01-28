#include "GxMaths/GxVector.h"

#include "GxMaths/GxMatrix.h"
#include "GxMaths/GxViewport.h"

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

Gx::Vec3 Gx::Vec3::unprojected(const Viewport &vp, const Matrix &world, const Matrix &view, const Matrix &proj) const
{
    Gx::Vec3 r;
    D3DXVec3Unproject(&r, this, &vp, &proj, &view, &world);

    return r;
}

Gx::Vec4 Gx::Vec4::transformed(const Gx::Matrix &v) const
{
    Vec4 r;
    D3DXVec4Transform(&r, this, &v);
    
    return r;
}
