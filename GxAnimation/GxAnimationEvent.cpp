#include "GxAnimationEvent.h"

Gx::AnimationEvent::AnimationEvent() : position(0)
{
}

Gx::AnimationEvent::AnimationEvent(float position, const std::string &data) : position(position), data(data)
{
}

