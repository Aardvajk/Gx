#ifndef GX_CYLINDERSHAPE_H
#define GX_CYLINDERSHAPE_H

#include <GxPhysics/GxShapes/GxShape.h>

#include <pcx/scoped_ptr.h>

class btCylinderShape;

namespace Gx
{

class CylinderShape : public Shape
{
public:
    CylinderShape(float radius, float height);
    virtual ~CylinderShape() override;

    float radius() const;
    float height() const;

private:
    pcx::scoped_ptr<btCylinderShape> shape;
};

}

#endif // GX_CYLINDERSHAPE_H
