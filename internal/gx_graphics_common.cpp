#include "internal/gx_graphics_common.h"

DWORD gx_detail_graphics_usage(Gx::Graphics::Usage::Flags v)
{
    DWORD r = 0;
    
    if(v & Gx::Graphics::Usage::Flag::Dynamic) r |= D3DUSAGE_DYNAMIC;
    if(v & Gx::Graphics::Usage::Flag::RenderTarget) r |= D3DUSAGE_RENDERTARGET;

    return r;
}

DWORD gx_detail_graphics_lock(Gx::Graphics::Lock::Flags v)
{
    DWORD r = 0;

    if(v & Gx::Graphics::Lock::Flag::Discard) r |= D3DLOCK_DISCARD;
    
    return r;
}

D3DPOOL gx_detail_graphics_pool(Gx::Graphics::Pool v)
{
    switch(v)
    {
        case Gx::Graphics::Pool::Managed: return D3DPOOL_MANAGED;

        default: return D3DPOOL_DEFAULT;
    }
}

D3DFORMAT gx_detail_graphics_format(Gx::Graphics::Format v)
{
    switch(v)
    {
        case Gx::Graphics::Format::X8R8G8B8: return D3DFMT_X8B8G8R8;
        case Gx::Graphics::Format::A8R8G8B8: return D3DFMT_A8B8G8R8;
        case Gx::Graphics::Format::R32F: return D3DFMT_R32F;

        default: return { };
    }
}

DWORD gx_detail_texture_filter(Gx::Texture::Filter v)
{
    switch(v)
    {
        case Gx::Texture::Filter::None: return D3DTEXF_NONE;
        case Gx::Texture::Filter::Point: return D3DTEXF_POINT;
        case Gx::Texture::Filter::Linear: return D3DTEXF_LINEAR;
        case Gx::Texture::Filter::Anisotropic: return D3DTEXF_ANISOTROPIC;

        default: return { };
    }
}
