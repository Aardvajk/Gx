#ifndef GXVECTOR_H
#define GXVECTOR_H

#include <d3dx9.h>

namespace Gx
{

class Vec2 : public D3DXVECTOR2
{
public:
    using D3DXVECTOR2::D3DXVECTOR2;
    
    float dot(const Vec2 &v){ return D3DXVec2Dot(this, &v); }
    float length() const { return D3DXVec2Length(this); }
};

class Vec3 : public D3DXVECTOR3
{
public:
    using D3DXVECTOR3::D3DXVECTOR3;

    float dot(const Vec3 &v){ return D3DXVec3Dot(this, &v); }
    float length() const { return D3DXVec3Length(this); }
};

class Vec4 : public D3DXVECTOR4
{
public:
    using D3DXVECTOR4::D3DXVECTOR4;

    float dot(const Vec4 &v){ return D3DXVec4Dot(this, &v); }
    float length() const { return D3DXVec4Length(this); }
};

}

#endif // GXVECTOR_H
