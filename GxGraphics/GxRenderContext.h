#ifndef GXRENDERCONTEXT_H
#define GXRENDERCONTEXT_H

class IDirect3DSurface9;

namespace Gx
{

class GraphicsDevice;
class Texture;
class DepthStencilSurface;

class RenderContext
{
public:
    RenderContext(GraphicsDevice &device);
    RenderContext(Texture &texture, DepthStencilSurface &depthStencil);
    ~RenderContext();

    void apply(GraphicsDevice &device);

private:
    IDirect3DSurface9 *r;
    IDirect3DSurface9 *d;
};

}

#endif // GXRENDERCONTEXT_H
