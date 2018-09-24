#ifndef GXDISPLAYSETTINGS_H
#define GXDISPLAYSETTINGS_H

#include <pcx/flags.h>

#include <GxCore/GxSize.h>

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

    using Options = pcx::flags<Option>;

    DisplaySettings() = default;
    DisplaySettings(const Size &size, Options options) : size(size), options(options) { }
    
    Size size;
    Options options;
};

}

template<> struct pcx_is_flag_enum<Gx::DisplaySettings::Option> : std::true_type { };

#endif // GXDISPLAYSETTINGS_H
