#ifndef GX_PHYSICSMODEL_H
#define GX_PHYSICSMODEL_H

#include <pcx/non_copyable.h>
#include <pcx/aligned_store.h>

namespace Gx
{

class Body;
class Shape;
class Matrix;

class PhysicsModel : public pcx::non_copyable
{
public:
    PhysicsModel();
    virtual ~PhysicsModel();

    Body *createBody(Shape *shape, const Matrix &transform, float mass);

    void update(float delta);

    const Body &body(int index) const;
    int count() const;

private:
    friend class Body;

    void releaseBody(Body *body);

    pcx::aligned_store<48> cache;
};

}

#endif // GX_PHYSICSMODEL_H
