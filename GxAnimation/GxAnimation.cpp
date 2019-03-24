#include "GxAnimation.h"

namespace
{

class Cache
{
public:
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

Gx::Animation::~Animation()
{
}

Gx::Animation &Gx::Animation::operator=(const Animation &other)
{
    cache.get<Cache>() = other.cache.get<Cache>();
    return *this;
}
