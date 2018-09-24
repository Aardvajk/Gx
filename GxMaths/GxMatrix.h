#ifndef GXMATRIX_H
#define GXMATRIX_H

#include <d3dx9.h>

namespace Gx
{

class Vec3;

class Matrix : public D3DXMATRIX
{
public:
    using D3DXMATRIX::D3DXMATRIX;
    
    static Matrix identity();
    static Matrix lookAt(const Vec3 &eye, const Vec3 &look, const Vec3 &up);
    static Matrix proj(float fov, float aspect, float nearClip, float farClip);
    
    static Matrix rotationX(float angle);
    static Matrix rotationY(float angle);
    static Matrix rotationZ(float angle);
    
    static Matrix translate(const Vec3 &value);
};

}

#endif // GXMATRIX_H
