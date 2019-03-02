#ifndef GX_PHYSICS_RAY_H
#define GX_PHYSICS_RAY_H

#include <GxMaths/GxRay.h>

#include <GxPhysics/GxPhysicsTypes.h>

#include <btBulletDynamicsCommon.h>

#include <pcx/optional.h>

class gx_physics_ray_callback : public btCollisionWorld::ClosestRayResultCallback
{
public:
    gx_physics_ray_callback(const btVector3 &from, const btVector3 &to) : btCollisionWorld::ClosestRayResultCallback(from, to) { }
};

pcx::optional<Gx::RayResult> gx_physics_raycast(btCollisionWorld *world, const Gx::Ray &ray, float max, btCollisionWorld::ClosestRayResultCallback &callback);

#endif // GX_PHYSICS_RAY_H
