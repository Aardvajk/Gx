#ifndef GXTIMER_H
#define GXTIMER_H

#include <GxCore/GxFlags.h>
#include <GxCore/GxWindows.h>

namespace Gx
{

class Timer
{
public:
    Timer();

    enum class Option { Restart = 1 };
    typedef Flags<Option> Options;

    float elapsed(Options options = Options());

private:
    LARGE_INTEGER frequency;
    LARGE_INTEGER lastCount;
};

}

template<> struct GxIsFlagEnum<Gx::Timer::Option> : std::true_type { };

#endif // GXTIMER_H
