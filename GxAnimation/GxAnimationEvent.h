#ifndef GXANIMATIONEVENT_H
#define GXANIMATIONEVENT_H

#include <pcx/shared_data.h>
#include <pcx/optional.h>
#include <pcx/datastream.h>

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

pcx::data_istream &operator>>(pcx::data_istream &ds, Gx::AnimationEvent &v);
pcx::data_ostream &operator<<(pcx::data_ostream &ds, const Gx::AnimationEvent &v);

#endif // GXANIMATIONEVENT_H
