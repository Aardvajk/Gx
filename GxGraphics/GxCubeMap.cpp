#include "GxCubeMap.h"

#include "GxGraphics/GxGraphicsDevice.h"

#include "internal/gx_common.h"
#include "internal/gx_graphics_common.h"

#include <stdexcept>
#include <d3dx9.h>

Gx::CubeMap::CubeMap() : ptr(nullptr)
{
}

Gx::CubeMap::CubeMap(GraphicsDevice &device, const Desc &desc) : d(desc), ptr(nullptr)
{
    reset(device);
}

Gx::CubeMap::CubeMap(GraphicsDevice &device, const std::vector<std::string> &paths, const Desc &desc) : d(desc), ptr(nullptr)
{
    reset(device);
    for(std::size_t i = 0; i < paths.size() && i < 6; ++i)
    {
        IDirect3DSurface9 *s = nullptr;
        ptr->GetCubeMapSurface(static_cast<D3DCUBEMAP_FACES>(i), 0, &s);

        if(!s)
        {
            throw std::runtime_error("unable to get cube map surface");
        }

        if(FAILED(D3DXLoadSurfaceFromFile(s, nullptr, nullptr, paths[i].c_str(), nullptr, D3DX_DEFAULT, 0, nullptr)))
        {
            s->Release();
            throw std::runtime_error("unable to load cube map surface");
        }

        s->Release();
    }
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
