#include "GxGraphics/GxGraphicsDevice.h"

#include "GxGraphics/GxVertexDeclaration.h"
#include "GxGraphics/GxShader.h"
#include "GxGraphics/GxVertexBuffer.h"
#include "GxGraphics/GxCubeMap.h"

#include "internal/gx_graphics_common.h"

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

void Gx::GraphicsDevice::setVertexDeclaration(const VertexDeclaration &declaratione)
{
    if(cache.get<Cache>().vertexDec != &declaratione)
    {
        device->SetVertexDeclaration(declaratione.ptr);
        cache.get<Cache>().vertexDec = &declaratione;
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

void Gx::GraphicsDevice::setVertexShader(const VertexShader &shader)
{
    if(cache.get<Cache>().vertexShader != &shader)
    {
        device->SetVertexShader(static_cast<IDirect3DVertexShader9*>(shader.ptr));
        shader.table->SetDefaults(device);

        cache.get<Cache>().vertexShader = &shader;
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

void Gx::GraphicsDevice::setPixelShader(const PixelShader &shader)
{
    if(cache.get<Cache>().pixelShader != &shader)
    {
        device->SetPixelShader(static_cast<IDirect3DPixelShader9*>(shader.ptr));
        shader.table->SetDefaults(device);

        cache.get<Cache>().pixelShader = &shader;
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

void Gx::GraphicsDevice::setTexture(unsigned stage, const CubeMap &cubeMap)
{
    device->SetTexture(stage, cubeMap.ptr);
}

void Gx::GraphicsDevice::setTexture(unsigned stage)
{
    device->SetTexture(stage, nullptr);
}

void Gx::GraphicsDevice::setTextureFilter(unsigned stage, Texture::Filter type)
{
    auto filter = gx_detail_texture_filter(type);

    device->SetSamplerState(stage, D3DSAMP_MAGFILTER, filter);
    device->SetSamplerState(stage, D3DSAMP_MINFILTER, filter);

    device->SetSamplerState(stage, D3DSAMP_MIPFILTER, filter);
}

void Gx::GraphicsDevice::clear(const Gx::Color &color, float z)
{
    device->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, color, z, 0);
}

void Gx::GraphicsDevice::clear(float z)
{
    device->Clear(0, NULL, D3DCLEAR_ZBUFFER, { }, z, 0);
}

void Gx::GraphicsDevice::renderTriangleList(const VertexBuffer &buffer, unsigned count)
{
    if(count)
    {
        device->SetStreamSource(0, reinterpret_cast<IDirect3DVertexBuffer9*>(buffer.ptr), 0, cache.get<Cache>().vertexDec->stride());
        device->SetIndices(0);

        device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, count);
    }
}

void Gx::GraphicsDevice::renderLineList(const VertexBuffer &buffer, unsigned count)
{
    if(count)
    {
        device->SetStreamSource(0, reinterpret_cast<IDirect3DVertexBuffer9*>(buffer.ptr), 0, cache.get<Cache>().vertexDec->stride());
        device->SetIndices(0);

        device->DrawPrimitive(D3DPT_LINELIST, 0, count);
    }
}

void Gx::GraphicsDevice::renderPointList(const VertexBuffer &buffer, unsigned count)
{
    if(count)
    {
        device->SetStreamSource(0, reinterpret_cast<IDirect3DVertexBuffer9*>(buffer.ptr), 0, cache.get<Cache>().vertexDec->stride());
        device->SetIndices(0);

        device->DrawPrimitive(D3DPT_POINTLIST, 0, count);
    }
}

void Gx::GraphicsDevice::setZBufferEnable(bool state)
{
    device->SetRenderState(D3DRS_ZENABLE, state);
}

void Gx::GraphicsDevice::setZWriteEnable(bool state)
{
    device->SetRenderState(D3DRS_ZWRITEENABLE, state);
}

void Gx::GraphicsDevice::setPointSize(float size)
{
    device->SetRenderState(D3DRS_POINTSIZE, *((DWORD*)(&size)));
}

void Gx::GraphicsDevice::setAlphaBlend(AlphaBlend type)
{
    if(type == AlphaBlend::Normal)
    {
        device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
        device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    }
    else if(type == AlphaBlend::Invert)
    {
        device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
        device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
        device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
    }
    else
    {
        device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
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

