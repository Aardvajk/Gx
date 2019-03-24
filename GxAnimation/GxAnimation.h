#ifndef GXANIMATION_H
#define GXANIMATION_H

#include <GxAnimation/GxKeyFrame.h>
#include <GxAnimation/GxAnimationEvent.h>

#include <pcx/aligned_store.h>

#include <vector>

namespace Gx
{

class Animation
{
public:
    Animation();
    Animation(const Animation &other);
    Animation(std::size_t count, float duration, const std::vector<KeyFrame> &keys, const std::vector<AnimationEvent> &events, bool loop);
    ~Animation();

    Animation &operator=(const Animation &other);

    KeyFrame keyFrame(float time) const;
    std::vector<AnimationEvent> events(float from, float to) const;

private:
    pcx::aligned_store<72> cache;
};

}

#endif // GXANIMATION_H
