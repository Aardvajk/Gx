#ifndef GX_CUBEMAP_H
#define GX_CUBEMAP_H

#include <GxGraphics/GxGraphicsTypes.h>
#include <GxGraphics/GxGraphicsResource.h>

class IDirect3DCubeTexture9;

namespace Gx
{

class CubeMap : public GraphicsResource
{
public:
    enum class Face : std::uint8_t
    {
        Right,
        Left,
        Top,
        Bottom,
        Front,
        Back        
    };

    struct Desc
    {
        unsigned size;
        unsigned mipLevels;
        Gx::Graphics::Usage::Flags usage;
        Gx::Graphics::Format format;
        Gx::Graphics::Pool pool;
    };

    CubeMap();
    explicit CubeMap(GraphicsDevice &device, const Desc &desc);
    virtual ~CubeMap() override;
    
    virtual void reset(GraphicsDevice &device) override;

    virtual void release() override;
    virtual bool isDeviceBound() const override;

    void reset(GraphicsDevice &device, const Desc &desc);

    unsigned size() const;

private:
    friend class RenderContext;

    Desc d;
    IDirect3DCubeTexture9 *ptr;
};

}

#endif // GX_CUBEMAP_H
