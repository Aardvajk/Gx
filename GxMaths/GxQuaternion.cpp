#include "GxMaths/GxQuaternion.h"

#include "GxMaths/GxVector.h"
#include "GxMaths/GxMatrix.h"

#include <cmath>

Gx::Matrix Gx::Quaternion::matrix() const
{
    Matrix m;
    D3DXMatrixRotationQuaternion(&m, this);

    return m;
}

Gx::Vec2 Gx::Quaternion::angle() const
{
    double sqx = x * x;
    double sqy = y * y;
    double sqz = z * z;

    float tx = atan2(2 * y * w - 2 * x * z, 1 - 2 * sqy - 2 * sqz);
    float ty = atan2(2 * x * w - 2 * y * z, 1 - 2 * sqx - 2 * sqz);

    return Vec2(tx, ty);
}

Gx::Quaternion Gx::Quaternion::interpolated(const Quaternion &v, float t) const
{
    Gx::Quaternion q;

    Gx::Quaternion n0;
    Gx::Quaternion n1;

    D3DXQuaternionNormalize(&n0, this);
    D3DXQuaternionNormalize(&n1, &v);

    D3DXQuaternionSlerp(&q, &n0, &n1, t);

    D3DXQuaternionNormalize(&q, &q);

    return q;
}

Gx::Quaternion Gx::Quaternion::identity()
{
    Quaternion q;
    D3DXQuaternionIdentity(&q);

    return q;
}

Gx::Quaternion Gx::Quaternion::axisRotation(const Vec3 &v)
{
    Quaternion q;
    D3DXQuaternionRotationYawPitchRoll(&q, v.y, v.x, v.z);

    return q;
}

Gx::Quaternion Gx::Quaternion::rotationBetween(const Gx::Vec3 &a, const Gx::Vec3 &b)
{
    Quaternion q;

    Vec3 v0 = a.normalized();
    Vec3 v1 = b.normalized();

    float d = v0.dot(v1);

    if(d >= 1.0f)
    {
        return Quaternion{ 0, 0, 0, 0 };
    }

    if(d < (1e-6f - 1.0f))
    {
        Vec3 axis = Vec3(1, 0, 0).cross(a);
        if(axis.dot(axis) == 0)
        {
            axis = Vec3(0, 1, 0).cross(a);
        }

        axis = axis.normalized();

        float ang = static_cast<float>(M_PI);
        D3DXQuaternionToAxisAngle(&q, &axis, &ang);
    }
    else
    {
        float s = std::sqrt((1 + d) * 2);
        float invs = 1 / s;

        Vec3 c = v0.cross(v1);

        q.x = c.x * invs;
        q.y = c.y * invs;
        q.z = c.z * invs;
        q.w = s * 0.5f;

        D3DXQuaternionNormalize(&q, &q);
    }

    return q;
}

