#include "GxShape.h"

#include "internal/gx_physics_common.h"

#include <BulletCollision/CollisionShapes/btConvexShape.h>

Gx::Shape::~Shape()
{
}

Gx::Shape::Shape() : collisionShape(nullptr), convexShape(nullptr)
{
}

Gx::Aabb Gx::Shape::aabb(const Matrix &transform) const
{
    btVector3 min = { }, max = { };
    if(convexShape)
    {
        convexShape->getAabb(gx_detail_physics_fromMatrix(transform), min, max);
    }

    return Aabb(gx_detail_physics_toVec3(min), gx_detail_physics_toVec3(max));
}
