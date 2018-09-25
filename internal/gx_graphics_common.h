#ifndef GX_GRAPHICS_COMMON_H
#define GX_GRAPHICS_COMMON_H

#include "GxGraphics/GxGraphicsTypes.h"

#include <d3d9.h>

DWORD gx_detail_graphics_usage(Gx::Graphics::Usage::Flags v);
DWORD gx_detail_graphics_lock(Gx::Graphics::Lock::Flags v);

D3DPOOL gx_detail_graphics_pool(Gx::Graphics::Pool v);

D3DFORMAT gx_detail_graphics_format(Gx::Graphics::Format v);

#endif // GX_GRAPHCIS_COMMON_H
