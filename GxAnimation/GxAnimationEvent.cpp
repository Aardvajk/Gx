#include "GxAnimationEvent.h"

#include <pcx/optional.h>

namespace
{

class Cache
{
public:
    Cache(pcx::optional<float> position, const std::string &data) : position(position), data(data) { }

    pcx::optional<float> position;
    std::string data;
};

}

Gx::AnimationEvent::AnimationEvent()
{
    cache.alloc<Cache>(pcx::nullopt, std::string());
}

Gx::AnimationEvent::AnimationEvent(const AnimationEvent &other)
{
    cache.alloc<Cache>(other.cache.get<Cache>());
}

Gx::AnimationEvent::AnimationEvent(float position, const std::string &data)
{
    cache.alloc<Cache>(position, data);
}

Gx::AnimationEvent::~AnimationEvent()
{
}

Gx::AnimationEvent &Gx::AnimationEvent::operator=(const AnimationEvent &other)
{
    cache.get<Cache>() = other.cache.get<Cache>();
    return *this;
}

bool Gx::AnimationEvent::valid() const
{
    return cache.get<Cache>().position;
}

float Gx::AnimationEvent::position() const
{
    return *cache.get<Cache>().position;
}

std::string Gx::AnimationEvent::data() const
{
    return cache.get<Cache>().data;
}
