#ifndef GX_ANIMATION_H
#define GX_ANIMATION_H

#include <GxAnimation/GxKeyFrame.h>
#include <GxAnimation/GxAnimationEvent.h>

#include <pcx/shared_data.h>

#include <vector>

namespace Gx
{

class Animation
{
public:
    Animation();
    Animation(std::size_t count, float duration, const std::vector<KeyFrame> &keys, const std::vector<AnimationEvent> &events, bool loop);

    float duration() const;

    KeyFrame keyFrame(float t) const;
    std::vector<AnimationEvent> events(float from, float to) const;

private:
    struct Data
    {
        std::size_t count;
        float duration;
        std::vector<Gx::KeyFrame> keys;
        std::vector<Gx::AnimationEvent> events;
        bool loop;
    };

    pcx::shared_data<Data> s;
};

}

#endif // GX_ANIMATION_H
