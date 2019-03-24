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

pcx::data_istream &operator>>(pcx::data_istream &ds, Gx::AnimationEvent &v)
{
    auto position = ds.get<float>();
    auto data = ds.get<std::string>();

    v = Gx::AnimationEvent(position, data);

    return ds;
}

pcx::data_ostream &operator<<(pcx::data_ostream &ds, const Gx::AnimationEvent &v)
{
    return ds << v.position() << v.data();
}
