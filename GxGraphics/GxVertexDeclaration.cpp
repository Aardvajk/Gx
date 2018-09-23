#include "GxGraphics/GxVertexDeclaration.h"

#include "GxGraphics/GxGraphicsDevice.h"

#include <stdexcept>
#include <d3d9.h>

namespace
{

const BYTE types[] =
{
    D3DDECLTYPE_FLOAT3,
    D3DDECLTYPE_FLOAT4,
    D3DDECLTYPE_D3DCOLOR,
    D3DDECLTYPE_FLOAT2,
};

const BYTE usages[] =
{
    D3DDECLUSAGE_POSITION,
    D3DDECLUSAGE_NORMAL,
    D3DDECLUSAGE_COLOR,
    D3DDECLUSAGE_TEXCOORD
};

const std::size_t sizes[] =
{
    12,
    16,
    4,
    8
};

}

Gx::VertexDeclaration::VertexDeclaration(std::vector<VertexElement> elements) : ptr(nullptr), elements(std::move(elements))
{
}

Gx::VertexDeclaration::~VertexDeclaration()
{
    release();
}

void Gx::VertexDeclaration::reset(GraphicsDevice &device)
{
    release();

    std::vector<D3DVERTEXELEMENT9> v;
    str = 0;

    for(const auto &e: elements)
    {
        v.push_back({ 0xFF, str, types[static_cast<int>(e.type)], D3DDECLMETHOD_DEFAULT, usages[static_cast<int>(e.type)], e.index });
        str += sizes[static_cast<int>(e.type)];
    }

    v.push_back({ 0xFF, 0, D3DDECLTYPE_UNUSED, 0, 0, 0 });

    if(FAILED(device.device->CreateVertexDeclaration(reinterpret_cast<const D3DVERTEXELEMENT9*>(v.data()), &ptr)))
    {
        throw std::runtime_error("unable to reset vertex declaration");
    }
}

void Gx::VertexDeclaration::release()
{
    if(ptr)
    {
        ptr->Release();
        ptr = nullptr;
    }
}

bool Gx::VertexDeclaration::isDeviceBound() const
{
    return false;
}

uint16_t Gx::VertexDeclaration::stride() const
{
    return str;
}
