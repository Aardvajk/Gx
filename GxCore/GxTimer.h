#ifndef GX_TIMER_H
#define GX_TIMER_H

#include <pcx/flags.h>

#include <GxCore/GxWindows.h>

namespace Gx
{

class Timer
{
public:
    Timer();

    enum class Flag : std::uint8_t
    {
        Restart = 1
    };
    
    using Flags = pcx::flags<Flag>;

    float elapsed(Flags flags = { });

private:
    LARGE_INTEGER frequency;
    LARGE_INTEGER lastCount;
};

}

template<> struct pcx_is_flag_enum<Gx::Timer::Flag> : std::true_type { };

#endif // GX_TIMER_H
