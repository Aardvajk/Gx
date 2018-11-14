#ifndef GX_INDEXBUFFER_H
#define GX_INDEXBUFFER_H

#include <GxGraphics/GxGraphicsTypes.h>
#include <GxGraphics/GxGraphicsResource.h>

#include <cstdint>

class IDirect3DIndexBuffer9;

namespace Gx
{

class IndexBuffer : public GraphicsResource
{
public:
    struct Desc
    {
        std::uint32_t elements;
        std::uint16_t stride;
        Graphics::Usage::Flags usage;
        Graphics::Pool pool;
    };

    explicit IndexBuffer(GraphicsDevice &device, const Desc &desc);
    virtual ~IndexBuffer() override;
    
    virtual void reset(GraphicsDevice &device) override;
    virtual void release() override;

    virtual bool isDeviceBound() const override;

    void *lock(Graphics::Lock::Flags flags);
    void unlock();

    unsigned bytes() const;
    std::uint16_t stride() const;

private:
    friend class GraphicsDevice;
    
    Desc d;
    IDirect3DIndexBuffer9 *ptr;
};

}

#endif // GX_INDEXBUFFER_H
