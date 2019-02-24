#ifndef GXSPHERESHAPE_H
#define GXSPHERESHAPE_H

#include <GxPhysics/GxShapes/GxShape.h>

#include <pcx/scoped_ptr.h>

class btSphereShape;

namespace Gx
{

class SphereShape : public Shape
{
public:
    explicit SphereShape(float radius);
    virtual ~SphereShape() override;

    float radius() const;

private:
    pcx::scoped_ptr<btSphereShape> shape;
};

}

#endif // GXSPHERESHAPE_H
