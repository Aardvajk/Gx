#ifndef GX_PHYSICSMODEL_H
#define GX_PHYSICSMODEL_H

#include <GxPhysics/GxPhysicsTypes.h>

#include <GxMaths/GxAabb.h>
#include <GxMaths/GxRay.h>

#include <pcx/non_copyable.h>
#include <pcx/aligned_store.h>
#include <pcx/optional.h>

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

    BroadphaseResult broadphase(const Aabb &aabb);
    pcx::optional<ConvexResult> convexIntersection(const Shape &shape1, const Matrix &transform1, const Shape &shape2, const Matrix &transform2);
    pcx::optional<RayResult> rayCast(const Ray &ray, float max);

    Body *createBody(Shape *shape, const Matrix &transform, float mass);

    void update(float delta);

    const Body &body(int index) const;
    int bodyCount() const;

private:
    friend class Body;

    void releaseBody(Body *body);

    pcx::aligned_store<48> cache;
};

}

#endif // GX_PHYSICSMODEL_H
