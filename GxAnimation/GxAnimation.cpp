#include "GxAnimation.h"

#include "GxMaths/GxRange.h"

#include "GxAnimation/GxAnimationEvent.h"

#include <pcx/fixed_array.h>

#include <vector>
#include <cmath>

#include <GxCore/GxDebug.h>

namespace
{

class Cache
{
public:
    std::size_t count;
    float duration;
    std::vector<Gx::KeyFrame> keys;
    std::vector<Gx::AnimationEvent> events;
    bool loop;
};

}

Gx::Animation::Animation()
{
    cache.alloc<Cache>();
}

Gx::Animation::Animation(const Animation &other)
{
    cache.alloc<Cache>(other.cache.get<Cache>());
}

Gx::Animation::Animation(std::size_t count, float duration, const std::vector<KeyFrame> &keys, const std::vector<AnimationEvent> &events, bool loop)
{
    auto &c = cache.alloc<Cache>();

    c.count = count;
    c.duration = duration;
    c.keys = keys;
    c.events = events;
    c.loop = loop;
}

Gx::Animation::~Animation()
{
}

Gx::Animation &Gx::Animation::operator=(const Animation &other)
{
    cache.get<Cache>() = other.cache.get<Cache>();
    return *this;
}

Gx::KeyFrame Gx::Animation::keyFrame(float time) const
{
    auto &c = cache.get<Cache>();
    if(c.keys.empty())
    {
        return KeyFrame();
    }

    float fr = static_cast<float>(c.count);

    float mod = c.loop ? fmod(time, 1) : time;
    float position = static_cast<float>(fr - 1.0f) * mod;

    if(position < c.keys.front().position)
    {
        std::size_t a = c.keys.size() - 1;
        std::size_t b = 0;

        float range = (c.keys[b].position + (fr - c.keys[a].position)) - 1;
        float offset = (position + (fr - c.keys[a].position)) - 1;

        return Interpolator<KeyFrame>()(c.keys[a], c.keys[b], offset / range);
    }

    if(position > c.keys.back().position && c.loop)
    {
        std::size_t a = c.keys.size() - 1;
        std::size_t b = 0;

        float range = (c.keys[b].position + (fr - c.keys[a].position)) - 1;
        float offset = position - c.keys[a].position;

        return Interpolator<KeyFrame>()(c.keys[a], c.keys[b], offset / range);
    }

    for(std::size_t i = 0; i < c.keys.size() - 1; ++i)
    {
        if(position >= c.keys[i].position && position < c.keys[i + 1].position)
        {
            float range = c.keys[i + 1].position - c.keys[i].position;
            float offset = position - c.keys[i].position;

            return Interpolator<KeyFrame>()(c.keys[i], c.keys[i + 1], offset / range);
        }
    }

    return c.keys.back();
}

std::vector<Gx::AnimationEvent> Gx::Animation::events(float from, float to) const
{
    auto &c = cache.get<Cache>();
    std::vector<AnimationEvent> fired;

    float fr = static_cast<float>(c.count);

    pcx::fixed_array<RangeF, 2> r;

    r.push_back(RangeF(static_cast<float>(fr - 1.0f) * std::fmod(from, 1), static_cast<float>(fr - 1.0f) * std::fmod(to, 1)));

    if(r[0].min > r[0].max)
    {
        r.push_back(r[0]);

        r[0].min -= fr;
        r[1].max += fr;
    }

    for(std::size_t i = 0; i < c.events.size(); ++i)
    {
        for(std::size_t j = 0; j < r.size(); ++j)
        {
            if(r[j].contains(c.events[i].position()))
            {
                fired.push_back(c.events[i]);
                break;
            }
        }
    }

    return fired;
}


