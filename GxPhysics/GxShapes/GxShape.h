#ifndef GXSHAPE_H
#define GXSHAPE_H

#include <GxMaths/GxAabb.h>

#include <pcx/non_copyable.h>

class btCollisionShape;
class btConvexShape;

namespace Gx
{

class Shape : public pcx::non_copyable
{
public:
    virtual ~Shape();

    Aabb aabb(const Matrix &transform) const;

protected:
    friend class PhysicsModel;

    Shape();

    btCollisionShape *collisionShape;
    btConvexShape *convexShape;
};

}

#endif // GXSHAPE_H
