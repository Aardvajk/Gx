#include "GxGraphics/GxTexture.h"

#include "GxGraphics/GxGraphicsDevice.h"

#include "internal/gx_common.h"
#include "internal/gx_graphics_common.h"

#include <stdexcept>
#include <d3dx9.h>

Gx::Texture::Texture(GraphicsDevice &device, const Desc &desc) : d(desc), ptr(nullptr)
{
    reset(device);
}

Gx::Texture::~Texture()
{
    release();
}

void Gx::Texture::reset(Gx::GraphicsDevice &device)
{
    release();

    HRESULT r = D3DXCreateTexture(device.device, d.size.width, d.size.height, d.mipLevels, gx_detail_graphics_usage(d.usage), gx_detail_graphics_format(d.format), gx_detail_graphics_pool(d.pool), &ptr);
    if(FAILED(r))
    {
        release();
        throw std::runtime_error("unable to create texture");
    }
}

void Gx::Texture::release()
{
    gx_detail_com_ptr_release(ptr);
}

bool Gx::Texture::isDeviceBound() const
{
    return d.pool != Graphics::Pool::Managed;
}

Gx::Size Gx::Texture::size() const
{
    D3DSURFACE_DESC desc;
    ptr->GetLevelDesc(0, &desc);

    return Size(desc.Width, desc.Height);
}
