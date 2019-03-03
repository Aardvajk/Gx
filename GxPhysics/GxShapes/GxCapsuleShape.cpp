#include "GxCapsuleShape.h"

#include <BulletCollision/CollisionShapes/btCapsuleShape.h>

Gx::CapsuleShape::CapsuleShape(float radius, float height) : shape(new btCapsuleShape(radius, height - (radius * 2)))
{
    collisionShape = shape.get();
    convexShape = shape.get();
}

Gx::CapsuleShape::~CapsuleShape()
{
}

float Gx::CapsuleShape::radius() const
{
    return shape->getRadius();
}

float Gx::CapsuleShape::height() const
{
    return (shape->getHalfHeight() * 2) + (shape->getRadius() * 2);
}
