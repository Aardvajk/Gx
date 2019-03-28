#ifndef GX_KEYFRAME_H
#define GX_KEYFRAME_H

#include <pcx/datastream.h>

#include <GxMaths/GxBlendValue.h>

#include <GxAnimation/GxJointTransform.h>

#include <vector>

namespace Gx
{

class KeyFrame
{
public:
    KeyFrame();
    explicit KeyFrame(std::size_t count);

    float position;
    std::vector<JointTransform> transforms;
};

template<> struct Interpolator<KeyFrame>
{
    KeyFrame operator()(const KeyFrame &a, const KeyFrame &b, float t) const;
};

class WeightedKey
{
public:
    WeightedKey();
    WeightedKey(const Gx::KeyFrame &key, float weight);

    KeyFrame key;
    float weight;
};

}

inline pcx::data_istream &operator>>(pcx::data_istream &ds, Gx::KeyFrame &v){ return ds >> v.position >> v.transforms; }
inline pcx::data_ostream &operator<<(pcx::data_ostream &ds, const Gx::KeyFrame &v){ return ds << v.position << v.transforms; }

#endif // GX_KEYFRAME_H
