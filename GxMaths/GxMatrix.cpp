#include "GxMaths/GxMatrix.h"

#include "GxMaths/GxSize.h"
#include "GxMaths/GxRange.h"
#include "GxMaths/GxVector.h"

Gx::Matrix Gx::Matrix::inverse() const
{
    Matrix m;
    D3DXMatrixInverse(&m, NULL, this);
    
    return m;
}

Gx::Matrix Gx::Matrix::identity()
{
    Matrix m;
    D3DXMatrixIdentity(&m);
    
    return m;    
}

Gx::Matrix Gx::Matrix::lookAt(const Gx::Vec3 &eye, const Gx::Vec3 &look, const Gx::Vec3 &up)
{
    Matrix m;
    D3DXMatrixLookAtLH(&m, &eye, &look, &up);

    return m;
}

Gx::Matrix Gx::Matrix::perspective(float fov, float aspect, const RangeF &clip)
{
    Matrix m;
    D3DXMatrixPerspectiveFovLH(&m, fov, aspect, clip.min, clip.max);
    
    return m;
}

Gx::Matrix Gx::Matrix::ortho(const SizeF &size, const RangeF &clip)
{
    Matrix m;
    D3DXMatrixOrthoLH(&m, size.width, size.height, clip.min, clip.max);

    return m;
}

Gx::Matrix Gx::Matrix::rotationX(float angle)
{
    Matrix m;
    D3DXMatrixRotationX(&m, angle);
    
    return m;
}

Gx::Matrix Gx::Matrix::rotationY(float angle)
{
    Matrix m;
    D3DXMatrixRotationY(&m, angle);
    
    return m;
}

Gx::Matrix Gx::Matrix::rotationZ(float angle)
{
    Matrix m;
    D3DXMatrixRotationZ(&m, angle);
    
    return m;
}

Gx::Matrix Gx::Matrix::rotationXYZ(const Vec3 &values)
{
    Matrix m;
    D3DXMatrixRotationYawPitchRoll(&m, values.x, values.y, values.z);

    return m;
}

Gx::Matrix Gx::Matrix::rotationAxis(const Vec3 &axis, float angle)
{
    Matrix m;
    D3DXMatrixRotationAxis(&m, &axis, angle);

    return m;
}

Gx::Matrix Gx::Matrix::translation(const Gx::Vec3 &values)
{
    Matrix m;
    D3DXMatrixTranslation(&m, values.x, values.y, values.z);
    
    return m;
}

Gx::Matrix Gx::Matrix::scaling(const Gx::Vec3 &values)
{
    Matrix m;
    D3DXMatrixScaling(&m, values.x, values.y, values.z);
    
    return m;
}
