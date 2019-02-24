#include "GxShape.h"

#include <BulletCollision/CollisionShapes/btConvexShape.h>

Gx::Shape::~Shape()
{
}

Gx::Shape::Shape() : collisionShape(nullptr), convexShape(nullptr)
{
}

