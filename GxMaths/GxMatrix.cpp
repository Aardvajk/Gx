#include "GxMaths/GxMatrix.h"

#include "GxMaths/GxVec3.h"

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
