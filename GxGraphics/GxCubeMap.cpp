#include "GxCubeMap.h"

#include "GxGraphics/GxGraphicsDevice.h"

#include "internal/gx_common.h"
#include "internal/gx_graphics_common.h"

#include <stdexcept>
#include <d3dx9.h>

Gx::CubeMap::CubeMap(GraphicsDevice &device, const Desc &desc) : d(desc), ptr(nullptr)
{
    reset(device);
}

Gx::CubeMap::~CubeMap()
{
    release();
}

void Gx::CubeMap::reset(Gx::GraphicsDevice &device)
{
    release();
    
    HRESULT r = D3DXCreateCubeTexture(device.device, d.size, d.mipLevels, gx_detail_graphics_usage(d.usage), gx_detail_graphics_format(d.format), gx_detail_graphics_pool(d.pool), &ptr);
    if(FAILED(r))
    {
        release();
        throw std::runtime_error("unable to create cube map");
    }
}

void Gx::CubeMap::release()
{
    gx_detail_com_ptr_release(ptr);
}

bool Gx::CubeMap::isDeviceBound() const
{
    return d.pool != Graphics::Pool::Managed;
}

void Gx::CubeMap::reset(GraphicsDevice &device, const Desc &desc)
{
    d = desc;
    reset(device);
}

unsigned Gx::CubeMap::size() const
{
    return d.size;
}
