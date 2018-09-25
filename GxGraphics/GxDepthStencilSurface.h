#ifndef GXDEPTHSTENCILSURFACE_H
#define GXDEPTHSTENCILSURFACE_H

#include <GxCore/GxSize.h>

#include <GxGraphics/GxGraphicsResource.h>

#include <cstdint>

class IDirect3DSurface9;

namespace Gx
{

class DepthStencilSurface : public GraphicsResource
{
public:
    enum class Format : std::uint8_t
    {
        D16,
        D32,
        D24S8
    };

    struct Desc
    {
        Size size;
        Format format;
    };

    explicit DepthStencilSurface(GraphicsDevice &device, const Desc &desc);
    virtual ~DepthStencilSurface() override;
    
    virtual void reset(GraphicsDevice &device) override;
    virtual void release() override;

    virtual bool isDeviceBound() const override;

    Size size() const;

private:
    Desc d;
    IDirect3DSurface9 *ptr;
};

}

#endif // GXDEPTHSTENCILSURFACE_H
