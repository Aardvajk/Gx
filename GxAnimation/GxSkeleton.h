#ifndef GX_SKELETON_H
#define GX_SKELETON_H

#include <GxAnimation/GxSkeletonJoint.h>

#include <GxMaths/GxMatrix.h>

#include <pcx/shared_data.h>

#include <string>
#include <vector>
#include <unordered_map>

namespace Gx
{

class KeyFrame;

class Skeleton
{
public:
    Skeleton();

    void addJoint(const std::string &name, const SkeletonJoint &joint);
    void setKeyFrame(const KeyFrame &key);

    SkeletonJoint joint(std::size_t index) const;
    Gx::Matrix transform(std::size_t index) const;

    std::vector<Gx::Matrix> palette() const;

    std::size_t size() const;

private:
    struct Data
    {
        std::vector<Gx::SkeletonJoint> joints;
        std::unordered_map<std::string, std::size_t> mapping;
        std::vector<Gx::Matrix> palette;
    };

    pcx::shared_data<Data> s;
};

}

#endif // GX_SKELETON_H
