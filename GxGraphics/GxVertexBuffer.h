#ifndef GX_VERTEXBUFFER_H
#define GX_VERTEXBUFFER_H

#include <GxGraphics/GxGraphicsTypes.h>
#include <GxGraphics/GxGraphicsResource.h>

class IDirect3DVertexBuffer9;

namespace Gx
{

class VertexBuffer : public GraphicsResource
{
public:
    struct Desc
    {
        std::uint32_t bytes;
        Graphics::Usage::Flags usage;
        Graphics::Pool pool;
    };
    
    explicit VertexBuffer(GraphicsDevice &device, const Desc &desc);
    virtual ~VertexBuffer() override;

    virtual void reset(GraphicsDevice &device) override;
    virtual void release() override;

    virtual bool isDeviceBound() const override;

    void *lock(Graphics::Lock::Flags flags);
    void unlock();

    unsigned bytes() const;

private:
    friend class GraphicsDevice;

    Desc d;
    IDirect3DVertexBuffer9 *ptr;
};

}

#endif // GX_VERTEXBUFFER_H
