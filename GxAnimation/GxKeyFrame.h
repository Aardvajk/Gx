#ifndef GXKEYFRAME_H
#define GXKEYFRAME_H

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

#endif // GXKEYFRAME_H
