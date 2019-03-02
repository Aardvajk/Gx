#include "gx_physics_gjk.h"

#include "internal/gx_physics_common.h"

pcx::optional<Gx::ConvexResult> gx_physics_gjk::intersection(const btConvexShape *shape1, const btTransform &transform1, const btConvexShape *shape2, const btTransform &transform2)
{
    btGjkPairDetector gjk(shape1, shape2, &voronoiSolver, &epaSolver);

    btDiscreteCollisionDetectorInterface::ClosestPointInput input;
    input.m_transformA = transform1;
    input.m_transformB = transform2;

    btPointCollector res;

    gjk.getClosestPointsNonVirtual(input, res, 0);

    if(res.m_hasResult && res.m_distance < 0)
    {
        Gx::ConvexResult r;

        r.point = gx_detail_physics_toVec3(res.m_pointInWorld);
        r.separatingVector = gx_detail_physics_toVec3(res.m_normalOnBInWorld).normalized() * -res.m_distance;

        return r;
    }

    return { };
}
