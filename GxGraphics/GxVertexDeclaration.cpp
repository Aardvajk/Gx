#include "GxGraphics/GxVertexDeclaration.h"

#include "GxGraphics/GxGraphicsTypes.h"
#include "GxGraphics/GxGraphicsDevice.h"

#include "internal/gx_common.h"

#include <GxCore/GxDebug.h>

#include <stdexcept>
#include <d3d9.h>

namespace
{

const BYTE types[] =
{
    D3DDECLTYPE_FLOAT3,
    D3DDECLTYPE_FLOAT3,
    D3DDECLTYPE_D3DCOLOR,
    D3DDECLTYPE_FLOAT2,
    D3DDECLTYPE_UBYTE4,
    D3DDECLTYPE_FLOAT4,
    D3DDECLTYPE_FLOAT3
};

const BYTE usages[] =
{
    D3DDECLUSAGE_POSITION,
    D3DDECLUSAGE_NORMAL,
    D3DDECLUSAGE_COLOR,
    D3DDECLUSAGE_TEXCOORD,
    D3DDECLUSAGE_BLENDINDICES,
    D3DDECLUSAGE_BLENDWEIGHT,
    D3DDECLUSAGE_TANGENT
};

const WORD sizes[] =
{
    12,
    12,
    4,
    8,
    4,
    16,
    12
};

const BYTE indices[] =
{
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

template<typename T> T get(const T t[], Gx::VertexElement e){ return t[static_cast<int>(e)]; }

}

Gx::VertexDeclaration::VertexDeclaration() : ptr(nullptr)
{
}

Gx::VertexDeclaration::VertexDeclaration(GraphicsDevice &device, std::vector<VertexElement> elements) : ptr(nullptr), elements(std::move(elements))
{
    reset(device);
}

Gx::VertexDeclaration::~VertexDeclaration()
{
    gx_detail_com_ptr_release(ptr);
}

void Gx::VertexDeclaration::reset(GraphicsDevice &device)
{
    release();

    std::vector<D3DVERTEXELEMENT9> v;
    str = 0;

    for(auto e: elements)
    {
        v.push_back({ 0, str, get(types, e), D3DDECLMETHOD_DEFAULT, get(usages, e), get(indices, e) });
        str += get(sizes, e);
    }

    v.push_back({ 0xFF, 0, D3DDECLTYPE_UNUSED, 0, 0, 0 });

    HRESULT r = device.device->CreateVertexDeclaration(v.data(), &ptr);
    if(FAILED(r))
    {
        release();
        throw std::runtime_error("unable to reset vertex declaration");
    }
}

void Gx::VertexDeclaration::release()
{
    gx_detail_com_ptr_release(ptr);
}

bool Gx::VertexDeclaration::isDeviceBound() const
{
    return false;
}

void Gx::VertexDeclaration::reset(GraphicsDevice &device, std::vector<VertexElement> data)
{
    elements = std::move(data);
    reset(device);
}

uint16_t Gx::VertexDeclaration::stride() const
{
    return str;
}
