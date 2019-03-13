#include "gx_physics_common.h"

namespace
{

Gx::Matrix prepareMatrixFromRULP(const Gx::Vec3 &r, const Gx::Vec3 &u, const Gx::Vec3 &l, const Gx::Vec3 &p)
{
    Gx::Matrix result;

    result._11 = r.x;result._12 = r.y;result._13 = r.z;result._14 = 0.f;
    result._21 = u.x;result._22 = u.y;result._23 = u.z;result._24 = 0.f;
    result._31 = l.x;result._32 = l.y;result._33 = l.z;result._34 = 0.f;
    result._41 = p.x;result._42 = p.y;result._43 = p.z;result._44 = 1.f;

    return result;
}

}

Gx::Matrix gx_detail_physics_toMatrix(const btTransform &m)
{
    btVector3 r = m.getBasis().getColumn(0);
    btVector3 u = m.getBasis().getColumn(1);
    btVector3 l = m.getBasis().getColumn(2);
    btVector3 p = m.getOrigin();

    Gx::Vec3 vR, vU, vL, vP;
    vR.x = r.x(); vR.y = r.y(); vR.z = r.z();
    vU.x = u.x(); vU.y = u.y(); vU.z = u.z();
    vL.x = l.x(); vL.y = l.y(); vL.z = l.z();
    vP.x = p.x(); vP.y = p.y(); vP.z = p.z();

    return prepareMatrixFromRULP(vR, vU, vL, vP);
}

btTransform gx_detail_physics_fromMatrix(const Gx::Matrix &m)
{
   btTransform transform;

   btVector3 r, u, l, p;
   r.setX(m._11); r.setY(m._12); r.setZ(m._13);
   u.setX(m._21); u.setY(m._22); u.setZ(m._23);
   l.setX(m._31); l.setY(m._32); l.setZ(m._33);
   p.setX(m._41); p.setY(m._42); p.setZ(m._43);

   transform.getBasis().setValue(r.x(), u.x(), l.x(), r.y(), u.y(), l.y(), r.z(), u.z(), l.z());

   transform.setOrigin(p);
   return transform;
}

Gx::Quaternion gx_detail_physics_toQuaternion(const btQuaternion &q)
{
    return Gx::Quaternion(q.x(), q.y(), q.z(), q.w());
}

btQuaternion gx_detail_physics_fromQuaternion(const Gx::Quaternion &q)
{
    return btQuaternion(q.x, q.y, q.z, q.w);
}
