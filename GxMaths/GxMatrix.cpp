#include "GxMaths/GxMatrix.h"

#include "GxMaths/GxVector.h"

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

Gx::Matrix Gx::Matrix::proj(float fov, float aspect, float nearClip, float farClip)
{
    Matrix m;
    D3DXMatrixPerspectiveFovLH(&m, fov, aspect, nearClip, farClip);
    
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

Gx::Matrix Gx::Matrix::translate(const Gx::Vec3 &value)
{
    Matrix m;
    D3DXMatrixTranslation(&m, value.x, value.y, value.z);
    
    return m;
}
