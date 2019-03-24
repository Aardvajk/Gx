#ifndef GX_SKELETONJOINT_H
#define GX_SKELETONJOINT_H

#include <GxMaths/GxVector.h>

#include <pcx/optional.h>

#include <cstdint>

namespace Gx
{

class SkeletonJoint
{
public:
    SkeletonJoint();
    SkeletonJoint(const Vec3 &offset, pcx::optional<std::uint8_t> parent);

    Vec3 offset;
    pcx::optional<std::uint8_t> parent;
};

}

#endif // GX_SKELETONJOINT_H
