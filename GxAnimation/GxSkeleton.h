#ifndef GX_SKELETON_H
#define GX_SKELETON_H

#include <GxMaths/GxMatrix.h>

#include <pcx/aligned_store.h>
#include <pcx/optional.h>

#include <vector>

namespace Gx
{

class SkeletonJoint;
class KeyFrame;

class Skeleton
{
public:
    Skeleton();
    Skeleton(const Skeleton &other);
    ~Skeleton();

    Skeleton &operator=(const Skeleton &other);

    void addJoint(const std::string &name, const SkeletonJoint &joint);
    void setKeyFrame(const KeyFrame &key);

    const SkeletonJoint &joint(std::size_t index) const;

    std::vector<Gx::Matrix> palette() const;

    std::size_t size() const;

private:
    pcx::aligned_store<104> cache;
};

}

#endif // GX_SKELETON_H
