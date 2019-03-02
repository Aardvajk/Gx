#include "gx_physics_broadphase.h"

#include <GxPhysics/GxBody.h>

#include <btBulletDynamicsCommon.h>

bool gx_physics_broadphase::process(const btBroadphaseProxy *proxy)
{
    btCollisionObject *o = static_cast<btCollisionObject*>(proxy->m_clientObject);

    if(btRigidBody *b = btRigidBody::upcast(o))
    {
        result.push_back(reinterpret_cast<Gx::Body*>(b->getUserPointer()));
        return true;
    }

    return false;
}

