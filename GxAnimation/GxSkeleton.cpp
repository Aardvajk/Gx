#include "GxSkeleton.h"

#include "GxMaths/GxMatrix.h"

#include "GxAnimation/GxSkeletonJoint.h"
#include "GxAnimation/GxJointTransform.h"
#include "GxAnimation/GxKeyFrame.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace
{

class Cache
{
public:
    std::vector<Gx::SkeletonJoint> joints;
    std::unordered_map<std::string, std::size_t> mapping;
    std::vector<Gx::Matrix> palette;
};

Gx::JointTransform get(const std::vector<Gx::JointTransform> &pose, std::size_t i)
{
    if(i >= pose.size()) return Gx::JointTransform();
    return pose[i];
}

Gx::Matrix buildMatrix(const Cache &c, std::size_t index, const std::vector<Gx::JointTransform> &pose)
{
    const auto &j = c.joints[index];

    if(j.parent)
    {
        auto p = *j.parent;

        auto t0 = Gx::Matrix::translation(-c.joints[p].offset);
        auto r = get(pose, index).rotation.matrix();
        auto t1 = Gx::Matrix::translation(c.joints[p].offset);

        return (t0 * r * t1) * Gx::Matrix::translation(get(pose, index).translation) * buildMatrix(c, p, pose);
    }

    return Gx::Matrix::translation(get(pose, index).translation);
}

}

Gx::Skeleton::Skeleton()
{
    cache.alloc<Cache>();
}

Gx::Skeleton::Skeleton(const Skeleton &other)
{
    cache.alloc<Cache>(other.cache.get<Cache>());
}

Gx::Skeleton::~Skeleton()
{
}

Gx::Skeleton &Gx::Skeleton::operator=(const Skeleton &other)
{
    cache.get<Cache>() = other.cache.get<Cache>();
    return *this;
}

void Gx::Skeleton::addJoint(const std::string &name, const SkeletonJoint &joint)
{
    auto &c = cache.get<Cache>();

    c.joints.push_back(joint);
    c.mapping[name] = c.joints.size() - 1;
}

void Gx::Skeleton::setKeyFrame(const KeyFrame &key)
{
    auto &c = cache.get<Cache>();

    c.palette.clear();

    c.palette.push_back(Gx::Matrix::identity());
    for(std::size_t i = 0; i < c.joints.size(); ++i)
    {
        c.palette.push_back(buildMatrix(c, i, key.transforms));
    }
}

const Gx::SkeletonJoint &Gx::Skeleton::joint(std::size_t index) const
{
    return cache.get<Cache>().joints[index];
}

std::vector<Gx::Matrix> Gx::Skeleton::palette() const
{
    return cache.get<Cache>().palette;
}

std::size_t Gx::Skeleton::size() const
{
    return cache.get<Cache>().joints.size();
}

