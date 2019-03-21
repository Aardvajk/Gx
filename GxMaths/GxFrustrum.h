#ifndef GX_FRUSTRUM_H
#define GX_FRUSTRUM_H

#include <d3dx9.h>
#include <vector>

namespace Gx
{

class Matrix;
class Vec3;
class Aabb;

class Frustrum
{
public:
    Frustrum();
    Frustrum(float depth, const Matrix &view, const Matrix &proj);

    bool contains(const Vec3 &pos) const;
    bool contains(const std::vector<Vec3> &hull) const;
    bool contains(const Aabb &aabb) const;

private:
    D3DXPLANE p[6];
};

}

#endif // GXFRUSTRUM_H
