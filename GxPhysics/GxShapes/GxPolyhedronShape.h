#ifndef GX_POLYHEDRONSHAPE_H
#define GX_POLYHEDRONSHAPE_H

#include <GxPhysics/GxShapes/GxShape.h>

#include <GxMaths/GxVector.h>

#include <pcx/fixed_array.h>
#include <pcx/scoped_ptr.h>

#include <vector>

class btConvexHullShape;

namespace Gx
{

class PolyhedronShape : public Shape
{
public:
    using Face = pcx::fixed_array<std::size_t, 4>;

    PolyhedronShape(const std::vector<Vec3> &vertices, const std::vector<Face> &faces);
    explicit PolyhedronShape(const Vec3 &dims);
    virtual ~PolyhedronShape() override;

    std::vector<Vec3> vertices() const;
    std::vector<Face> faces() const;

    static PolyhedronShape *cuboid(const Vec3 &dims);

private:
    pcx::scoped_ptr<btConvexHullShape> shape;

    std::vector<Vec3> vs;
    std::vector<Face> fs;
};

}

#endif // GX_POLYHEDRONSHAPE_H
