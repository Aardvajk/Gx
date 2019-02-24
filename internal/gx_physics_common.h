#ifndef GX_PHYSICS_COMMON_H
#define GX_PHYSICS_COMMON_H

#include <GxMaths/GxVector.h>
#include <GxMaths/GxMatrix.h>

#include <LinearMath/btVector3.h>
#include <LinearMath/btTransform.h>

inline Gx::Vec3 gx_detail_physics_toVec3(const btVector3 &v){ return Gx::Vec3(v.x(), v.y(), v.z()); }
inline btVector3 gx_detail_physics_fromVec3(const Gx::Vec3 &v){ return btVector3(v.x, v.y, v.z); }

Gx::Matrix gx_detail_physics_toMatrix(const btTransform &m);
btTransform gx_detail_physics_fromMatrix(const Gx::Matrix &m);

#endif // GX_PHYSICS_COMMON_H
