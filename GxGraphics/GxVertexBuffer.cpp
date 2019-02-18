#include "GxGraphics/GxVertexBuffer.h"

#include "GxGraphics/GxGraphicsDevice.h"

#include "internal/gx_common.h"
#include "internal/gx_graphics_common.h"

#include <stdexcept>
#include <d3d9.h>

Gx::VertexBuffer::VertexBuffer(GraphicsDevice &device, const Desc &desc) : d(desc), ptr(nullptr)
{
    reset(device);
}

Gx::VertexBuffer::~VertexBuffer()
{
    release();
}

void Gx::VertexBuffer::reset(Gx::GraphicsDevice &device)
{
    release();

    HRESULT r = device.device->CreateVertexBuffer(d.bytes, gx_detail_graphics_usage(d.usage), 0, gx_detail_graphics_pool(d.pool), &ptr, 0);
    if(FAILED(r))
    {
        release();
        throw std::runtime_error("unable to create vertex buffer");
    }
}

void Gx::VertexBuffer::release()
{
    gx_detail_com_ptr_release(ptr);
}

bool Gx::VertexBuffer::isDeviceBound() const
{
    return d.pool != Graphics::Pool::Managed;
}

void *Gx::VertexBuffer::lock(Graphics::Lock::Flags flags)
{
    void *data;
    if(!FAILED(ptr->Lock(0, 0, &data, gx_detail_graphics_lock(flags))))
    {
        return data;
    }

    return nullptr;
}

void Gx::VertexBuffer::unlock()
{
    ptr->Unlock();
}

unsigned Gx::VertexBuffer::bytes() const
{
    return d.bytes;
}
