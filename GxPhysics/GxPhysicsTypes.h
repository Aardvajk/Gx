#ifndef GX_PHYSICSTYPES_H
#define GX_PHYSICSTYPES_H

#include <GxMaths/GxVector.h>

#include <vector>

namespace Gx
{

class Body;

using BroadphaseResult = std::vector<Body*>;

struct ConvexResult
{
    Vec3 point;
    Vec3 separatingVector;
};

struct RayResult
{
    Body *body;
    Vec3 point;
    Vec3 normal;
    float distance;
};

}

#endif // GXPHYSICSTYPES_H
