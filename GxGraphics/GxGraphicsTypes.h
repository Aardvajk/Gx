#ifndef GX_GRAPHICSTYPES_H
#define GX_GRAPHICSTYPES_H

#include <pcx/flags.h>

namespace Gx
{

namespace Graphics
{

namespace Usage
{

enum class Flag : std::uint8_t
{
    Dynamic = 1,
    RenderTarget = 2
};

using Flags = pcx::flags<Flag>;

}

namespace Lock
{

enum class Flag : std::uint8_t
{
    Discard = 1
};

using Flags = pcx::flags<Flag>;

}

enum class Pool : std::uint8_t
{
    Default,
    Managed
};

enum class Format : std::uint8_t
{
    X8R8G8B8,
    A8R8G8B8,
    R32F
};

}

}

template<> struct pcx_is_flag_enum<Gx::Graphics::Usage::Flag> : std::true_type { };
template<> struct pcx_is_flag_enum<Gx::Graphics::Lock::Flag> : std::true_type { };

#endif // GX_GRAPHICSTYPEE_H
