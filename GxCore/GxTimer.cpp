#include "GxTimer.h"

Gx::Timer::Timer()
{
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&lastCount);
}

float Gx::Timer::elapsed(Flags flags)
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);

    float time = static_cast<float>(count.QuadPart - lastCount.QuadPart)/static_cast<float>(frequency.QuadPart);

    if(flags & Flag::Restart)
    {
        lastCount = count;
    }

    return time > 0.25f ? 0.25f : time;
}
