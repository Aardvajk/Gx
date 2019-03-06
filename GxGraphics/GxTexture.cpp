#include "GxGraphics/GxTexture.h"

#include "GxGraphics/GxGraphicsDevice.h"

#include "internal/gx_common.h"
#include "internal/gx_graphics_common.h"

#include <stdexcept>
#include <d3dx9.h>

Gx::Texture::Texture() : ptr(nullptr)
{
}

Gx::Texture::Texture(GraphicsDevice &device, const Desc &desc) : d(desc), ptr(nullptr)
{
    reset(device);
}

Gx::Texture::Texture(GraphicsDevice &device, const std::string &path, const Desc &desc) : d(desc), ptr(nullptr)
{
    if(FAILED(D3DXCreateTextureFromFileEx(device.device, path.c_str(), 0, 0, d.mipLevels, gx_detail_graphics_usage(d.usage), gx_detail_graphics_format(d.format), gx_detail_graphics_pool(d.pool), D3DX_DEFAULT, D3DX_FILTER_LINEAR, 0, 0, 0, &ptr)))
    {
        throw std::runtime_error("unable to load texture");
    }
}

Gx::Texture::~Texture()
{
    release();
}

void Gx::Texture::reset(Gx::GraphicsDevice &device)
{
    release();

    if(FAILED(D3DXCreateTexture(device.device, d.size.width, d.size.height, d.mipLevels, gx_detail_graphics_usage(d.usage), gx_detail_graphics_format(d.format), gx_detail_graphics_pool(d.pool), &ptr)))
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

void Gx::Texture::reset(GraphicsDevice &device, const Desc &desc)
{
    d = desc;
    reset(device);
}

Gx::Size Gx::Texture::size() const
{
    D3DSURFACE_DESC desc;
    ptr->GetLevelDesc(0, &desc);

    return Size(desc.Width, desc.Height);
}
