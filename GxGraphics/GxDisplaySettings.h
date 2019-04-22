#ifndef GX_DISPLAYSETTINGS_H
#define GX_DISPLAYSETTINGS_H

#include <pcx/flags.h>

#include <GxMaths/GxSize.h>

namespace Gx
{

class DisplaySettings
{
public:
    enum class Flag : std::uint8_t
    {
        None = 0,
        Windowed = 1,
        VSync = 2
    };

    using Flags = pcx::flags<Flag>;

    DisplaySettings() = default;
    DisplaySettings(const Size &size, Flags options, unsigned multisampling) : size(size), options(options), multisampling(multisampling) { }
    
    Size size;
    Flags options;
    unsigned multisampling;
};

}

template<> struct pcx_is_flag_enum<Gx::DisplaySettings::Flag> : std::true_type { };

#endif // GX_DISPLAYSETTINGS_H
