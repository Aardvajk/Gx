#include "GxGraphics/GxDepthStencilSurface.h"

#include "GxGraphics/GxGraphicsDevice.h"

#include "internal/gx_common.h"

#include <stdexcept>
#include <d3dx9.h>

namespace
{

D3DFORMAT format(Gx::DepthStencilSurface::Format value)
{
    switch(value)
    {
        case Gx::DepthStencilSurface::Format::D16: return D3DFMT_D16;
        case Gx::DepthStencilSurface::Format::D32: return D3DFMT_D32;
        case Gx::DepthStencilSurface::Format::D24S8: return D3DFMT_D24S8;

        default: return { };
    }
}

}

Gx::DepthStencilSurface::DepthStencilSurface() : ptr(nullptr)
{
}

Gx::DepthStencilSurface::DepthStencilSurface(GraphicsDevice &device, const Desc &desc) : d(desc), ptr(nullptr)
{
    reset(device);
}

Gx::DepthStencilSurface::~DepthStencilSurface()
{
    release();
}

void Gx::DepthStencilSurface::reset(Gx::GraphicsDevice &device)
{
    release();
    
    HRESULT r = device.device->CreateDepthStencilSurface(d.size.width, d.size.height, format(d.format), D3DMULTISAMPLE_NONE, 0, FALSE, &ptr, NULL);
    if(FAILED(r))
    {
        release();
        throw std::runtime_error("unable to create depth stencil surface");
    }
}

void Gx::DepthStencilSurface::release()
{
    gx_detail_com_ptr_release(ptr);
}

bool Gx::DepthStencilSurface::isDeviceBound() const
{
    return true;
}

void Gx::DepthStencilSurface::reset(GraphicsDevice &device, const Desc &desc)
{
    d = desc;
    reset(device);
}

Gx::Size Gx::DepthStencilSurface::size() const
{
    D3DSURFACE_DESC desc;
    ptr->GetDesc(&desc);

    return Size(desc.Width, desc.Height);
}
