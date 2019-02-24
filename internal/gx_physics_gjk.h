#ifndef GX_PHYSICS_GJK_H
#define GX_PHYSICS_GJK_H

#include <GxPhysics/GxPhysicsTypes.h>

#include <btBulletDynamicsCommon.h>

#include <BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.h>
#include <BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h>
#include <BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h>
#include <BulletCollision/NarrowPhaseCollision/btPointCollector.h>

#include <pcx/optional.h>

class gx_physics_gjk
{
public:
    gx_physics_gjk() = default;

    pcx::optional<Gx::Physics::ConvexResult> intersection(const btConvexShape *shape1, const btTransform &transform1, const btConvexShape *shape2, const btTransform &transform2);

private:
    btVoronoiSimplexSolver voronoiSolver;
    btGjkEpaPenetrationDepthSolver epaSolver;
};

#endif // GX_PHYSICS_GJK_H
