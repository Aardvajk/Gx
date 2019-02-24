#include "GxPolyhedronShape.h"

#include "internal/gx_physics_common.h"

#include <BulletCollision/CollisionShapes/btConvexHullShape.h>

Gx::PolyhedronShape::PolyhedronShape(const std::vector<Vec3> &vertices, const std::vector<Face> &faces) : shape(new btConvexHullShape()), vs(vertices), fs(faces)
{
    collisionShape = shape.get();
    convexShape = shape.get();

    for(auto v: vertices) shape->addPoint(gx_detail_physics_fromVec3(v));
}

Gx::PolyhedronShape::~PolyhedronShape()
{
}

std::vector<Gx::Vec3> Gx::PolyhedronShape::vertices() const
{
    return vs;
}

std::vector<Gx::PolyhedronShape::Face> Gx::PolyhedronShape::faces() const
{
    return fs;
}
