#ifndef GXVECTOR_H
#define GXVECTOR_H

#include <d3dx9.h>

namespace Gx
{

class Vec2 : public D3DXVECTOR2
{
public:
    using D3DXVECTOR2::D3DXVECTOR2;
};

class Vec3 : public D3DXVECTOR3
{
public:
    using D3DXVECTOR3::D3DXVECTOR3;
};

class Vec4 : public D3DXVECTOR4
{
public:
    using D3DXVECTOR4::D3DXVECTOR4;
};

}

#endif // GXVECTOR_H
