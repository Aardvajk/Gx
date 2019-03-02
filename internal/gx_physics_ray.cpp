#include "gx_physics_ray.h"

#include "internal/gx_physics_common.h"

pcx::optional<Gx::RayResult> gx_physics_raycast(btCollisionWorld *world, const Gx::Ray &ray, float max, btCollisionWorld::ClosestRayResultCallback &callback)
{
    world->rayTest(gx_detail_physics_fromVec3(ray.position), gx_detail_physics_fromVec3(ray.position + (ray.direction * max)), callback);

    if(callback.m_collisionObject)
    {
        if(const btRigidBody *b = btRigidBody::upcast(callback.m_collisionObject))
        {
            Gx::RayResult result;

            result.body = static_cast<Gx::Body*>(b->getUserPointer());
            result.point = gx_detail_physics_toVec3(callback.m_hitPointWorld);
            result.normal = gx_detail_physics_toVec3(callback.m_hitNormalWorld).normalized();
            result.distance = Gx::Vec3(ray.position - result.point).length();

            return result;
        }
    }

    return { };
}
