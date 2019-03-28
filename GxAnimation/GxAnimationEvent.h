#ifndef GX_ANIMATIONEVENT_H
#define GX_ANIMATIONEVENT_H

#include <pcx/datastream.h>

#include <string>

namespace Gx
{

class AnimationEvent
{
public:
    AnimationEvent();
    AnimationEvent(float position, const std::string &data);

    float position;
    std::string data;
};

}

inline pcx::data_istream &operator>>(pcx::data_istream &ds, Gx::AnimationEvent &v){ return ds >> v.position >> v.data; }
inline pcx::data_ostream &operator<<(pcx::data_ostream &ds, const Gx::AnimationEvent &v){ return ds << v.position << v.data; }

#endif // GX_ANIMATIONEVENT_H
