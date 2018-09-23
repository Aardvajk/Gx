#ifndef GXVERTEXBUFFER_H
#define GXVERTEXBUFFER_H

#include <GxGraphics/GxGraphicsCore.h>
#include <GxGraphics/GxGraphicsResource.h>

class IDirect3DVertexBuffer9;

namespace Gx
{

class VertexBuffer : public GraphicsResource
{
public:
    struct Desc
    {
        std::uint32_t elements;
        std::uint16_t stride;
        Graphics::Usage::Flags usage;
        Graphics::Pool pool;
    };
    
    explicit VertexBuffer(const Desc &desc) : d(desc), ptr(nullptr) { }
    ~VertexBuffer();

    virtual void reset(GraphicsDevice &device) override;
    virtual void release() override;

    virtual bool isDeviceBound() const override;

    void *lock(Graphics::Lock::Flags flags);
    void unlock();

private:
    Desc d;
    IDirect3DVertexBuffer9 *ptr;
};

}

#endif // GXVERTEXBUFFER_H