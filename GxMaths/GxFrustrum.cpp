#include "GxMaths/GxFrustrum.h"

#include "GxMaths/GxMatrix.h"
#include "GxMaths/GxVector.h"
#include "GxMaths/GxAabb.h"

Gx::Frustrum::Frustrum()
{
}

Gx::Frustrum::Frustrum(float depth, const Matrix &view, const Matrix &proj)
{
    Matrix localProj = proj;

    float zMin = -proj._43 / proj._33;
    float r = depth / (depth - zMin);

    localProj._33 = r;
    localProj._43 = -r * zMin;

    Matrix matrix = view * localProj;

    // near
    p[0].a = matrix._14 + matrix._13;
    p[0].b = matrix._24 + matrix._23;
    p[0].c = matrix._34 + matrix._33;
    p[0].d = matrix._44 + matrix._43;

    // far
    p[1].a = matrix._14 - matrix._13;
    p[1].b = matrix._24 - matrix._23;
    p[1].c = matrix._34 - matrix._33;
    p[1].d = matrix._44 - matrix._43;

    // left
    p[2].a = matrix._14 + matrix._11;
    p[2].b = matrix._24 + matrix._21;
    p[2].c = matrix._34 + matrix._31;
    p[2].d = matrix._44 + matrix._41;

    // right
    p[3].a = matrix._14 - matrix._11;
    p[3].b = matrix._24 - matrix._21;
    p[3].c = matrix._34 - matrix._31;
    p[3].d = matrix._44 - matrix._41;

    // top
    p[4].a = matrix._14 - matrix._12;
    p[4].b = matrix._24 - matrix._22;
    p[4].c = matrix._34 - matrix._32;
    p[4].d = matrix._44 - matrix._42;

    // bottom
    p[5].a = matrix._14 + matrix._12;
    p[5].b = matrix._24 + matrix._22;
    p[5].c = matrix._34 + matrix._32;
    p[5].d = matrix._44 + matrix._42;

    for(int i = 0; i < 6; ++i)
    {
        D3DXPlaneNormalize(&p[i], &p[i]);
    }
}

bool Gx::Frustrum::contains(const Vec3 &pos) const
{
    auto p4 = Vec4(pos.x, pos.y, pos.z, 0);

    for(int i = 0; i < 6; ++i)
    {
        if(D3DXPlaneDotCoord(&p[i], &p4) < 0.0f)
        {
            return false;
        }
    }

    return true;
}

bool Gx::Frustrum::contains(const std::vector<Vec3> &hull) const
{
    for(int i = 0; i < 6; ++i)
    {
        std::size_t fails = 0;

        for(auto &v: hull)
        {
            auto p4 = Vec4(v.x, v.y, v.z, 0);
            if(D3DXPlaneDotCoord(&p[i], &p4) < 0.0f) ++fails;
        }

        if(fails == hull.size()) return false;
    }

    return true;
}

bool Gx::Frustrum::contains(const Aabb &aabb) const
{
    std::vector<Vec3> v(8);

    v[0] = Vec3(aabb.min.x, aabb.min.y, aabb.min.z);
    v[1] = Vec3(aabb.max.x, aabb.min.y, aabb.min.z);
    v[2] = Vec3(aabb.min.x, aabb.min.y, aabb.max.z);
    v[3] = Vec3(aabb.max.x, aabb.min.y, aabb.max.z);

    v[4] = Vec3(aabb.min.x, aabb.max.y, aabb.min.z);
    v[5] = Vec3(aabb.max.x, aabb.max.y, aabb.min.z);
    v[6] = Vec3(aabb.min.x, aabb.max.y, aabb.max.z);
    v[7] = Vec3(aabb.max.x, aabb.max.y, aabb.max.z);

    return contains(v);
}
