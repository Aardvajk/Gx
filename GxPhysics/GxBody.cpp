#include "GxBody.h"

#include "GxPhysics/GxPhysicsModel.h"
#include "GxPhysics/GxShapes/GxShape.h"

#include "internal/gx_physics_common.h"

#include <btBulletDynamicsCommon.h>

Gx::Body::~Body()
{
    model->releaseBody(this);
}

Gx::Matrix Gx::Body::matrix() const
{
    btTransform tr;
    ptr->getMotionState()->getWorldTransform(tr);

    return gx_detail_physics_toMatrix(tr);
}

Gx::Transform Gx::Body::transform() const
{
    btTransform tr;
    ptr->getMotionState()->getWorldTransform(tr);

    return Transform(gx_detail_physics_toVec3(tr.getOrigin()), gx_detail_physics_toQuaternion(tr.getRotation()));
}

const Gx::Shape &Gx::Body::shape() const
{
    return *sh;
}

Gx::Body::Body(PhysicsModel *model, btRigidBody *body, Shape *shape) : model(model), ptr(body), sh(shape)
{
}
