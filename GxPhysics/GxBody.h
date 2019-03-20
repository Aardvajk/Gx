#ifndef GXBODY_H
#define GXBODY_H

#include <GxMaths/GxMatrix.h>
#include <GxMaths/GxTransform.h>

#include <pcx/non_copyable.h>
#include <pcx/scoped_ptr.h>

class btRigidBody;

namespace Gx
{

class PhysicsModel;
class Shape;

class Body : public pcx::non_copyable
{
public:
    virtual ~Body();

    Matrix matrix() const;
    Transform transform() const;

    void applyCentralForce(const Vec3 &v);

    const Shape &shape() const;

private:
    friend class PhysicsModel;

    Body(PhysicsModel *model, btRigidBody *body, Shape *shape);

    PhysicsModel *model;
    btRigidBody *ptr;
    pcx::scoped_ptr<Shape> sh;
};

}

#endif // GXBODY_H
