#include "GxAnimationEvent.h"

#include <pcx/optional.h>

namespace
{

class Cache
{
public:
    pcx::optional<float> position;
    std::string data;
};

}

Gx::AnimationEvent::AnimationEvent()
{
    cache.alloc<Cache>();
}

Gx::AnimationEvent::AnimationEvent(const AnimationEvent &other)
{
    cache.alloc<Cache>(other.cache.get<Cache>());
}

Gx::AnimationEvent::AnimationEvent(float position, const std::string &data)
{
    auto &c = cache.alloc<Cache>();

    c.position = position;
    c.data = data;
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
