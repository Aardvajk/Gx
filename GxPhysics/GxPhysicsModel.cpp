#include "GxPhysicsModel.h"

#include "GxCore/GxDebug.h"

#include "GxPhysics/GxBody.h"
#include "GxPhysics/GxShapes/GxShape.h"

#include "internal/gx_physics_common.h"
#include "internal/gx_physics_gjk.h"

#include <btBulletDynamicsCommon.h>

#include <pcx/scoped_ptr.h>

namespace
{

class Cache
{
public:
    Cache();

    pcx::scoped_ptr<btDefaultCollisionConfiguration> collisionConfiguration;
    pcx::scoped_ptr<btCollisionDispatcher> dispatcher;
    pcx::scoped_ptr<btBroadphaseInterface> overlappingPairCache;
    pcx::scoped_ptr<btSequentialImpulseConstraintSolver> solver;

    pcx::scoped_ptr<btDiscreteDynamicsWorld> world;

    pcx::scoped_ptr<gx_physics_gjk> gjk;
};

Cache::Cache()
{
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration.get());
    overlappingPairCache = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();

    world = new btDiscreteDynamicsWorld(dispatcher.get(), overlappingPairCache.get(), solver.get(), collisionConfiguration.get());

    gjk = new gx_physics_gjk();
}

}

Gx::PhysicsModel::PhysicsModel()
{
    cache.alloc<Cache>();
}

Gx::PhysicsModel::~PhysicsModel()
{
}

Gx::Body *Gx::PhysicsModel::createBody(Shape *shape, const Matrix &transform, float mass)
{
    auto &c = cache.get<Cache>();

    btCollisionShape *colShape = shape->collisionShape;

    btTransform startTransform = gx_detail_physics_fromMatrix(transform);

    btVector3 localInertia(0,0,0);
    if(mass)
    {
        colShape->calculateLocalInertia(mass, localInertia);
    }

    btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, colShape, localInertia);

    btRigidBody *rigidBody = new btRigidBody(info);

    Body *body = new Body(this, rigidBody, shape);
    rigidBody->setUserPointer(body);

    c.world->addRigidBody(rigidBody);

    return body;
}

void Gx::PhysicsModel::update(float delta)
{
    cache.get<Cache>().world->stepSimulation(delta, 10);
}

const Gx::Body &Gx::PhysicsModel::body(int index) const
{
    return *(reinterpret_cast<const Body*>(cache.get<Cache>().world->getCollisionObjectArray()[index]->getUserPointer()));
}

int Gx::PhysicsModel::count() const
{
    return cache.get<Cache>().world->getCollisionObjectArray().size();
}

void Gx::PhysicsModel::releaseBody(Body *body)
{
    cache.get<Cache>().world->removeCollisionObject(body->ptr);
}

