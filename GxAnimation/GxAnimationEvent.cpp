#include "GxAnimationEvent.h"

Gx::AnimationEvent::AnimationEvent() : s(pcx::optional<float>(), std::string())
{
}

Gx::AnimationEvent::AnimationEvent(float position, const std::string &data) : s(pcx::optional<float>(position), data)
{
}

bool Gx::AnimationEvent::valid() const
{
    return s.value().position;
}

float Gx::AnimationEvent::position() const
{
    return *s.value().position;
}

std::string Gx::AnimationEvent::data() const
{
    return s.value().data;
}
