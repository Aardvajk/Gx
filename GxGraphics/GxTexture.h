#ifndef GXTEXTURE_H
#define GXTEXTURE_H

#include <GxCore/GxSize.h>

#include <GxGraphics/GxGraphicsCore.h>
#include <GxGraphics/GxGraphicsResource.h>

class IDirect3DTexture9;

namespace Gx
{

class Texture : public GraphicsResource
{
public:
    struct Desc
    {
        Size size;
        unsigned mipLevels;
        Graphics::Usage::Flags usage;
        Graphics::Format format;
        Graphics::Pool pool;
    };

    explicit Texture(GraphicsDevice &device, const Desc &desc);
    virtual ~Texture() override;
    
    virtual void reset(GraphicsDevice &device) override;
    virtual void release() override;

    virtual bool isDeviceBound() const override;

    Size size() const;

private:
    friend class GraphicsDevice;
    friend class RenderContext;

    Desc d;
    IDirect3DTexture9 *ptr;
};

}

#endif // GXTEXTURE_H
