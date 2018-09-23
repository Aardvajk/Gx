#include "internal/gx_common.h"

DWORD gx_detail_d3d_usage(Gx::Graphics::Usage::Flags v)
{
    DWORD r = 0;
    
    if(v & Gx::Graphics::Usage::Flag::Dynamic) r |= D3DUSAGE_DYNAMIC;
    if(v & Gx::Graphics::Usage::Flag::RenderTarget) r |= D3DUSAGE_RENDERTARGET;

    return r;
}

DWORD gx_detail_d3d_lock(Gx::Graphics::Lock::Flags v)
{
    DWORD r = 0;

    if(v & Gx::Graphics::Lock::Flag::Discard) r |= D3DLOCK_DISCARD;
    
    return r;
}

D3DPOOL gx_detail_d3d_pool(Gx::Graphics::Pool v)
{
    switch(v)
    {
        case Gx::Graphics::Pool::Managed: return D3DPOOL_MANAGED;

        default: return D3DPOOL_MANAGED;
    }
}
