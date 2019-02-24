#include "GxSphereShape.h"

#include <BulletCollision/CollisionShapes/btSphereShape.h>

Gx::SphereShape::SphereShape(float radius) : shape(new btSphereShape(radius))
{
    collisionShape = shape.get();
    convexShape = shape.get();
}

Gx::SphereShape::~SphereShape()
{
}

float Gx::SphereShape::radius() const
{
    return shape->getRadius();
}

