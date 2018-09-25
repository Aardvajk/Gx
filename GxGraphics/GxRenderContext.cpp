#include "GxGraphics/GxRenderContext.h"

#include "GxGraphics/GxGraphicsDevice.h"
#include "GxGraphics/GxTexture.h"
#include "GxGraphics/GxDepthStencilSurface.h"

#include <d3d9.h>

Gx::RenderContext::RenderContext(GraphicsDevice &device)
{
    device.device->GetRenderTarget(0, &r);
    device.device->GetDepthStencilSurface(&d);
}

Gx::RenderContext::RenderContext(Texture &texture, DepthStencilSurface &depthStencil)
{
    texture.ptr->GetSurfaceLevel(0, &r);

    d = depthStencil.ptr;
    d->AddRef();
}

Gx::RenderContext::RenderContext(CubeMap &texture, CubeMap::Face face, DepthStencilSurface &depthStencil)
{
    texture.ptr->GetCubeMapSurface(static_cast<D3DCUBEMAP_FACES>(face), 0, &r);

    d = depthStencil.ptr;
    d->AddRef();
}

Gx::RenderContext::~RenderContext()
{
    r->Release();
    d->Release();
}

void Gx::RenderContext::apply(GraphicsDevice &device)
{
    device.device->SetRenderTarget(0, r);
    device.device->SetDepthStencilSurface(d);
}
