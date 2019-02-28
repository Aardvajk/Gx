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

Gx::PolyhedronShape *Gx::PolyhedronShape::cuboid(const Vec3 &dims)
{
    Vec3 d = dims * 0.5f;

    std::vector<Vec3> vs;

    vs.push_back(Vec3(-d.x, d.y, -d.z));
    vs.push_back(Vec3(d.x, d.y, -d.z));
    vs.push_back(Vec3(d.x, -d.y, -d.z));
    vs.push_back(Vec3(-d.x, -d.y, -d.z));

    vs.push_back(Vec3(-d.x, d.y, d.z));
    vs.push_back(Vec3(d.x, d.y, d.z));
    vs.push_back(Vec3(d.x, -d.y, d.z));
    vs.push_back(Vec3(-d.x, -d.y, d.z));

    std::vector<Face> fs;

    fs.push_back(Face({ 0, 1, 2, 3 }));
    fs.push_back(Face({ 1, 5, 6, 2 }));
    fs.push_back(Face({ 4, 0, 3, 7 }));
    fs.push_back(Face({ 5, 4, 7, 6 }));
    fs.push_back(Face({ 4, 5, 1, 0 }));
    fs.push_back(Face({ 3, 2, 6, 7 }));

    return new PolyhedronShape(vs, fs);
}
