#ifndef GX_PHYSICS_BROADPHASE_H
#define GX_PHYSICS_BROADPHASE_H

#include <GxPhysics/GxPhysicsTypes.h>

#include <btBulletCollisionCommon.h>

#include <vector>

class gx_physics_broadphase : public btBroadphaseAabbCallback
{
public:
    gx_physics_broadphase(Gx::BroadphaseResult &result) : result(result) { }

    virtual bool process(const btBroadphaseProxy *proxy);

    Gx::BroadphaseResult &result;
};

#endif // GX_PHYSICS_BROADPHASE_H
