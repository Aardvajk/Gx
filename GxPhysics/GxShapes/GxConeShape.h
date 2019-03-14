#ifndef GXCONESHAPE_H
#define GXCONESHAPE_H

#include <GxPhysics/GxShapes/GxShape.h>

#include <pcx/scoped_ptr.h>

class btConeShape;

namespace Gx
{

class ConeShape : public Gx::Shape
{
public:
    ConeShape(float radius, float height);
    virtual ~ConeShape() override;

    float radius() const;
    float height() const;

private:
    pcx::scoped_ptr<btConeShape> shape;
};

}

#endif // GXCONESHAPE_H
