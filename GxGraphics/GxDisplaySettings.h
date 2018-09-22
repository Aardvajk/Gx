#ifndef GXDISPLAYSETTINGS_H
#define GXDISPLAYSETTINGS_H

#include <GxCore/GxSize.h>
#include <GxCore/GxFlags.h>

namespace Gx
{

class DisplaySettings
{
public:
    enum class Option : std::uint8_t
    {
        None = 0,
        Windowed = 1,
        VSync = 2
    };

    using Options = Flags<Option>;

    DisplaySettings() = default;
    DisplaySettings(const Size &size, Options options) : size(size), options(options) { }
    
    Size size;
    Options options;
};

}

template<> struct GxIsFlagEnum<Gx::DisplaySettings::Option> : std::true_type { };

#endif // GXDISPLAYSETTINGS_H
