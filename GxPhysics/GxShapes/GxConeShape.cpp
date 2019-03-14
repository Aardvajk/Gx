#include "GxConeShape.h"

#include <BulletCollision/CollisionShapes/btConeShape.h>

Gx::ConeShape::ConeShape(float radius, float height) : shape(new btConeShape(radius, height))
{
    collisionShape = shape.get();
    convexShape = shape.get();
}

Gx::ConeShape::~ConeShape()
{
}

float Gx::ConeShape::radius() const
{
    return shape->getRadius();
}

float Gx::ConeShape::height() const
{
    return shape->getHeight();
}
