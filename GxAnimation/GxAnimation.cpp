#include "GxAnimation.h"

#include "GxMaths/GxRange.h"

#include "GxAnimation/GxAnimationEvent.h"

#include <pcx/fixed_array.h>

#include <vector>
#include <cmath>

Gx::Animation::Animation() : s(0u, 0.0f, std::vector<KeyFrame>(), std::vector<AnimationEvent>(), false)
{
}

Gx::Animation::Animation(std::size_t count, float duration, const std::vector<KeyFrame> &keys, const std::vector<AnimationEvent> &events, bool loop) : s(count, duration, keys, events, loop)
{
}

float Gx::Animation::duration() const
{
    return s.value().duration;
}

Gx::KeyFrame Gx::Animation::keyFrame(float t) const
{
    auto &v = s.value();
    if(v.keys.empty())
    {
        return KeyFrame();
    }

    float fr = static_cast<float>(v.count);

    float mod = v.loop ? fmod(t, 1) : t;
    float position = static_cast<float>(fr - 1.0f) * mod;

    if(position < v.keys.front().position)
    {
        std::size_t a = v.keys.size() - 1;
        std::size_t b = 0;

        float range = (v.keys[b].position + (fr - v.keys[a].position)) - 1;
        float offset = (position + (fr - v.keys[a].position)) - 1;

        return Interpolator<KeyFrame>()(v.keys[a], v.keys[b], offset / range);
    }

    if(position > v.keys.back().position && v.loop)
    {
        std::size_t a = v.keys.size() - 1;
        std::size_t b = 0;

        float range = (v.keys[b].position + (fr - v.keys[a].position)) - 1;
        float offset = position - v.keys[a].position;

        return Interpolator<KeyFrame>()(v.keys[a], v.keys[b], offset / range);
    }

    for(std::size_t i = 0; i < v.keys.size() - 1; ++i)
    {
        if(position >= v.keys[i].position && position < v.keys[i + 1].position)
        {
            float range = v.keys[i + 1].position - v.keys[i].position;
            float offset = position - v.keys[i].position;

            return Interpolator<KeyFrame>()(v.keys[i], v.keys[i + 1], offset / range);
        }
    }

    return v.keys.back();
}

std::vector<Gx::AnimationEvent> Gx::Animation::events(float from, float to) const
{
    auto &v = s.value();
    std::vector<AnimationEvent> fired;

    float fr = static_cast<float>(v.count);

    pcx::fixed_array<RangeF, 2> r;

    r.push_back(RangeF(static_cast<float>(fr - 1.0f) * std::fmod(from, 1), static_cast<float>(fr - 1.0f) * std::fmod(to, 1)));

    if(r[0].min > r[0].max)
    {
        r.push_back(r[0]);

        r[0].min -= fr;
        r[1].max += fr;
    }

    for(std::size_t i = 0; i < v.events.size(); ++i)
    {
        for(std::size_t j = 0; j < r.size(); ++j)
        {
            if(r[j].contains(v.events[i].position()))
            {
                fired.push_back(v.events[i]);
                break;
            }
        }
    }

    return fired;
}


