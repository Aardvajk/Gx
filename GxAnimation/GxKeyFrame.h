#ifndef GXKEYFRAME_H
#define GXKEYFRAME_H

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

}

inline pcx::data_istream &operator>>(pcx::data_istream &ds, Gx::KeyFrame &v){ return ds >> v.position >> v.transforms; }
inline pcx::data_ostream &operator<<(pcx::data_ostream &ds, const Gx::KeyFrame &v){ return ds << v.position << v.transforms; }

#endif // GXKEYFRAME_H
