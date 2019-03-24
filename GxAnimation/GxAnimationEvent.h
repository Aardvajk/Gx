#ifndef GXANIMATIONEVENT_H
#define GXANIMATIONEVENT_H

#include <pcx/aligned_store.h>

#include <string>

namespace Gx
{

class AnimationEvent
{
public:
    AnimationEvent();
    AnimationEvent(const AnimationEvent &other);
    AnimationEvent(float position, const std::string &data);
    ~AnimationEvent();

    AnimationEvent &operator=(const AnimationEvent &other);

    bool valid() const;
    float position() const;
    std::string data() const;

private:
    pcx::aligned_store<64> cache;
};

}

#endif // GXANIMATIONEVENT_H
