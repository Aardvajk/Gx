#include "GxSkeletonJoint.h"

Gx::SkeletonJoint::SkeletonJoint() : offset(0, 0, 0), parent({ })
{
}

Gx::SkeletonJoint::SkeletonJoint(const Vec3 &offset, pcx::optional<std::uint8_t> parent) : offset(offset), parent(parent)
{
}
