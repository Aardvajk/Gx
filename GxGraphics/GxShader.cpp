#include "GxGraphics/GxShader.h"

#include "GxGraphics/GxGraphicsDevice.h"

#include "internal/gx_common.h"

#include <vector>
#include <stdexcept>
#include <d3dx9.h>

Gx::AbstractShader::~AbstractShader()
{
    release();
}

void Gx::AbstractShader::reset(Gx::GraphicsDevice &device)
{
    release();

    HRESULT r;
    if(type == Type::Vertex)
    {
        r = device.device->CreateVertexShader(reinterpret_cast<DWORD*>(buffer.data()), reinterpret_cast<IDirect3DVertexShader9**>(&ptr));
    }
    else
    {
        r = device.device->CreatePixelShader(reinterpret_cast<DWORD*>(buffer.data()), reinterpret_cast<IDirect3DPixelShader9**>(&ptr));
    }

    if(FAILED(r))
    {
        throw std::runtime_error("unable to create shader");
    }
}

void Gx::AbstractShader::release()
{
    gx_detail_com_ptr_release(table);
    gx_detail_com_ptr_release(ptr);
}

bool Gx::AbstractShader::isDeviceBound() const
{
    return false;
}
