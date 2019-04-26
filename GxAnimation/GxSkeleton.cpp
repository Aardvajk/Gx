#include "GxSkeleton.h"

#include "GxAnimation/GxJointTransform.h"
#include "GxAnimation/GxKeyFrame.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace
{

Gx::JointTransform get(const std::vector<Gx::JointTransform> &pose, std::size_t i)
{
    if(i >= pose.size()) return Gx::JointTransform();
    return pose[i];
}

Gx::Matrix buildMatrix(const std::vector<Gx::SkeletonJoint> &joints, std::size_t index, const std::vector<Gx::JointTransform> &pose)
{
    const auto &j = joints[index];

    if(j.parent)
    {
        auto p = *j.parent;

        auto t0 = Gx::Matrix::translation(-joints[p].offset);
        auto r = get(pose, index).rotation.matrix();
        auto t1 = Gx::Matrix::translation(joints[p].offset);

        return (t0 * r * t1) * Gx::Matrix::translation(get(pose, index).translation) * buildMatrix(joints, p, pose);
    }

    return Gx::Matrix::translation(get(pose, index).translation);
}

}

Gx::Skeleton::Skeleton()
{
}

void Gx::Skeleton::addJoint(const std::string &name, const SkeletonJoint &joint)
{
    auto &v = s.value();

    v.joints.push_back(joint);
    v.mapping[name] = v.joints.size() - 1;
}

void Gx::Skeleton::setKeyFrame(const KeyFrame &key)
{
    auto &v = s.value();

    v.palette.clear();

    v.palette.push_back(Gx::Matrix::identity());
    for(std::size_t i = 0; i < v.joints.size(); ++i)
    {
        v.palette.push_back(buildMatrix(v.joints, i, key.transforms));
    }
}

Gx::SkeletonJoint Gx::Skeleton::joint(std::size_t index) const
{
    return s.value().joints[index];
}

Gx::Matrix Gx::Skeleton::transform(std::size_t index) const
{
    return s.value().palette[index + 1];
}

std::vector<Gx::Matrix> Gx::Skeleton::palette() const
{
    return s.value().palette;
}

std::size_t Gx::Skeleton::size() const
{
    return s.value().joints.size();
}

