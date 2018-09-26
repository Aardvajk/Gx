#include "GxGraphics/GxGraphicsDevice.h"

#include "GxGraphics/GxVertexDeclaration.h"
#include "GxGraphics/GxShader.h"
#include "GxGraphics/GxVertexBuffer.h"
#include "GxGraphics/GxIndexBuffer.h"
#include "GxGraphics/GxTexture.h"

#include "GxMaths/GxColor.h"

#include <memory>
#include <d3d9.h>

namespace
{

class Cache
{
public:
    Cache() : vertexDec(nullptr), vertexShader(nullptr), pixelShader(nullptr) { }

    const Gx::VertexDeclaration *vertexDec;
    const Gx::VertexShader *vertexShader;
    const Gx::PixelShader *pixelShader;
};

}

Gx::GraphicsDevice::GraphicsDevice() : direct3d(nullptr), device(nullptr)
{
    cache.alloc<Cache>();
}

void Gx::GraphicsDevice::setVertexDeclaration(const VertexDeclaration &resource)
{
    if(cache.get<Cache>().vertexDec != &resource)
    {
        device->SetVertexDeclaration(resource.ptr);
        cache.get<Cache>().vertexDec = &resource;
    }
}

void Gx::GraphicsDevice::setVertexDeclaration()
{
    if(cache.get<Cache>().vertexDec)
    {
        device->SetVertexDeclaration(nullptr);
        cache.get<Cache>().vertexDec = nullptr;
    }
}

void Gx::GraphicsDevice::setVertexShader(const VertexShader &resource)
{
    if(cache.get<Cache>().vertexShader != &resource)
    {
        device->SetVertexShader(static_cast<IDirect3DVertexShader9*>(resource.ptr));
        resource.table->SetDefaults(device);

        cache.get<Cache>().vertexShader = &resource;
    }
}

void Gx::GraphicsDevice::setVertexShader()
{
    if(cache.get<Cache>().vertexShader)
    {
        device->SetVertexShader(nullptr);
        cache.get<Cache>().vertexShader = nullptr;
    }
}

void Gx::GraphicsDevice::setPixelShader(const PixelShader &resource)
{
    if(cache.get<Cache>().pixelShader != &resource)
    {
        device->SetPixelShader(static_cast<IDirect3DPixelShader9*>(resource.ptr));
        resource.table->SetDefaults(device);

        cache.get<Cache>().pixelShader = &resource;
    }
}

void Gx::GraphicsDevice::setPixelShader()
{
    if(cache.get<Cache>().pixelShader)
    {
        device->SetPixelShader(nullptr);
        cache.get<Cache>().pixelShader = nullptr;
    }
}

void Gx::GraphicsDevice::setTexture(unsigned stage, const Texture &texture)
{
    device->SetTexture(stage, texture.ptr);
}

void Gx::GraphicsDevice::setTexture(unsigned stage)
{
    device->SetTexture(stage, nullptr);
}

void Gx::GraphicsDevice::clear(const Gx::Color &color, float z)
{
    device->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, color, z, 0);
}

void Gx::GraphicsDevice::renderTriangleList(const VertexBuffer &buffer)
{
    if(buffer.bytes() / cache.get<Cache>().vertexDec->stride() >= 3)
    {
        device->SetStreamSource(0, reinterpret_cast<IDirect3DVertexBuffer9*>(buffer.ptr), 0, cache.get<Cache>().vertexDec->stride());
        device->SetIndices(0);
    
        device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, (buffer.bytes() / cache.get<Cache>().vertexDec->stride()) / 3);
    }
}

void Gx::GraphicsDevice::renderTriangleList(const VertexBuffer &buffer, const IndexBuffer &indices)
{
    if(indices.bytes() > 0 && ((indices.bytes() / indices.stride()) % 3) == 0)
    {
        device->SetStreamSource(0, buffer.ptr, 0, cache.get<Cache>().vertexDec->stride());
        device->SetIndices(indices.ptr);
    
        device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, buffer.bytes() / cache.get<Cache>().vertexDec->stride(), 0, (indices.bytes() / indices.stride()) / 3);
    }
}

bool Gx::GraphicsDevice::isOk() const
{
    return device->TestCooperativeLevel() == D3D_OK;
}

bool Gx::GraphicsDevice::isReadyToReset() const
{
    return device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET;
}

void Gx::GraphicsDevice::clearCache()
{
    cache.get<Cache>() = { };
}
