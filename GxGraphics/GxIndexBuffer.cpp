#include "GxIndexBuffer.h"

#include "GxGraphics/GxGraphicsDevice.h"

#include "internal/gx_common.h"
#include "internal/gx_graphics_common.h"

#include <stdexcept>
#include <d3dx9.h>

Gx::IndexBuffer::IndexBuffer(GraphicsDevice &device, const Desc &desc) : d(desc), ptr(nullptr)
{
    reset(device);
}

Gx::IndexBuffer::~IndexBuffer()
{
    release();
}

void Gx::IndexBuffer::reset(Gx::GraphicsDevice &device)
{
    D3DFORMAT format = (d.stride == 16 ? D3DFMT_INDEX16 : D3DFMT_INDEX32);

    HRESULT r = device.device->CreateIndexBuffer(d.elements * d.stride, gx_detail_graphics_usage(d.usage), format, gx_detail_graphics_pool(d.pool), &ptr, 0);
    if(FAILED(r))
    {
        release();
        throw std::runtime_error("unable to create index buffer");
    }
}

void Gx::IndexBuffer::release()
{
    gx_detail_com_ptr_release(ptr);
}

bool Gx::IndexBuffer::isDeviceBound() const
{
    return d.pool != Graphics::Pool::Managed;
}

void *Gx::IndexBuffer::lock(Gx::Graphics::Lock::Flags flags)
{
    void *data;
    if(!FAILED(ptr->Lock(0, 0, &data, gx_detail_graphics_lock(flags))))
    {
        return data;
    }

    return nullptr;
}

void Gx::IndexBuffer::unlock()
{
    ptr->Unlock();    
}

unsigned Gx::IndexBuffer::bytes() const
{
    return d.elements * d.stride;
}

std::uint16_t Gx::IndexBuffer::stride() const
{
    return d.stride;
}
