#ifndef GXANIMATION_H
#define GXANIMATION_H

#include <pcx/aligned_store.h>

namespace Gx
{

class Animation
{
public:
    Animation();
    Animation(const Animation &other);
    ~Animation();

    Animation &operator=(const Animation &other);

private:
    pcx::aligned_store<24> cache;
};

}

#endif // GXANIMATION_H
