#include "GxCylinderShape.h"

#include <BulletCollision/CollisionShapes/btCylinderShape.h>

Gx::CylinderShape::CylinderShape(float radius, float height) : shape(new btCylinderShape({ radius, height / 2, radius }))
{
    collisionShape = shape.get();
    convexShape = shape.get();
}

Gx::CylinderShape::~CylinderShape()
{
}

float Gx::CylinderShape::radius() const
{
    return shape->getHalfExtentsWithMargin().x();
}

float Gx::CylinderShape::height() const
{
    return shape->getHalfExtentsWithMargin().y() * 2;
}
