#ifndef GXANIMATIONEVENT_H
#define GXANIMATIONEVENT_H

#include <pcx/shared_data.h>
#include <pcx/optional.h>

#include <string>

namespace Gx
{

class AnimationEvent
{
public:
    AnimationEvent();
    AnimationEvent(float position, const std::string &data);

    bool valid() const;
    float position() const;
    std::string data() const;

private:
    struct Data
    {
        pcx::optional<float> position;
        std::string data;
    };

    pcx::shared_data<Data> s;
};

}

#endif // GXANIMATIONEVENT_H
