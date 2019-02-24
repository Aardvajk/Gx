#ifndef GX_AUDIOTYPES_H
#define GX_AUDIOTYPES_H

#include <pcx/flags.h>

namespace Gx
{

namespace Audio
{

namespace Caps
{

enum class Flag : std::uint8_t
{
    Volume = 1,
    Notify = 2
};

using Flags = pcx::flags<Flag>;

}

namespace Play
{

enum class Flag : std::uint8_t
{
    Loop = 1
};

using Flags = pcx::flags<Flag>;

}

}

}

template<> struct pcx_is_flag_enum<Gx::Audio::Caps::Flag> : std::true_type { };
template<> struct pcx_is_flag_enum<Gx::Audio::Play::Flag> : std::true_type { };

#endif // GX_AUDIOTYPES_H
