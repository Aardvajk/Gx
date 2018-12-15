#ifndef GX_MATRIX_H
#define GX_MATRIX_H

#include <d3dx9.h>

namespace Gx
{

class Vec3;
class SizeF;
class RangeF;

class Matrix : public D3DXMATRIX
{
public:
    using D3DXMATRIX::D3DXMATRIX;
    
    Matrix() = default;
    Matrix(const D3DXMATRIX &v) : D3DXMATRIX(v) { }
    
    Matrix inverse() const;
    
    static Matrix identity();
    static Matrix lookAt(const Vec3 &eye, const Vec3 &look, const Vec3 &up);
    static Matrix perspective(float fov, float aspect, const RangeF &clip);
    static Matrix ortho(const SizeF &size, const RangeF &clip);

    static Matrix rotationX(float angle);
    static Matrix rotationY(float angle);
    static Matrix rotationZ(float angle);
    static Matrix rotationXYZ(const Vec3 &values);
    static Matrix rotationAxis(const Vec3 &axis, float angle);
    
    static Matrix translation(const Vec3 &values);
    static Matrix scaling(const Vec3 &values);
};

}

#endif // GX_MATRIX_H
