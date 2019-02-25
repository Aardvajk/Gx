#ifndef GX_RENDERCONTEXT_H
#define GX_RENDERCONTEXT_H

#include <GxGraphics/GxCubeMap.h>

#include <pcx/non_copyable.h>

class IDirect3DSurface9;

namespace Gx
{

class GraphicsDevice;
class Texture;
class DepthStencilSurface;

class RenderContext : public pcx::non_copyable
{
public:
    RenderContext(GraphicsDevice &device);
    RenderContext(Texture &texture, DepthStencilSurface &depthStencil);
    RenderContext(CubeMap &texture, CubeMap::Face face, DepthStencilSurface &depthStencil);
    ~RenderContext();

    void apply(GraphicsDevice &device);

private:
    IDirect3DSurface9 *r;
    IDirect3DSurface9 *d;
};

}

#endif // GX_RENDERCONTEXT_H
