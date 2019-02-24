#ifndef GXCAPSULESHAPE_H
#define GXCAPSULESHAPE_H

#include <GxPhysics/GxShapes/GxShape.h>

#include <pcx/scoped_ptr.h>

class btCapsuleShape;

namespace Gx
{

class CapsuleShape : public Shape
{
public:
    CapsuleShape(float radius, float height);
    virtual ~CapsuleShape() override;

    float radius() const;
    float height() const;

private:
    pcx::scoped_ptr<btCapsuleShape> shape;
};

}

#endif // GXCAPSULESHAPE_H
