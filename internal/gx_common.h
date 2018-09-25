#ifndef GX_COMMON_H
#define GX_COMMON_H

#include "GxGraphics/GxGraphicsCore.h"

#include <d3d9.h>

template<typename T> void gx_detail_com_ptr_release(T *&ptr)
{
    if(ptr)
    {
        ptr->Release();
        ptr = nullptr;
    }
}

DWORD gx_detail_d3d_usage(Gx::Graphics::Usage::Flags v);
DWORD gx_detail_d3d_lock(Gx::Graphics::Lock::Flags v);

D3DPOOL gx_detail_d3d_pool(Gx::Graphics::Pool v);

D3DFORMAT gx_detail_d3d_format(Gx::Graphics::Format v);

#endif
