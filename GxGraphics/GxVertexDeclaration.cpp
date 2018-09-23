#include "GxGraphics/GxVertexDeclaration.h"

#include "GxGraphics/GxGraphicsDevice.h"

#include <stdexcept>
#include <d3d9.h>

Gx::VertexDeclaration::VertexDeclaration(std::vector<VertexElement> elements, WORD size) : ptr(nullptr), elements(std::move(elements)), sz(size)
{
}

Gx::VertexDeclaration::~VertexDeclaration()
{
    release();
}

void Gx::VertexDeclaration::reset(GraphicsDevice &device)
{
    release();

    if(FAILED(device.device->CreateVertexDeclaration(reinterpret_cast<const D3DVERTEXELEMENT9*>(elements.data()), &ptr)))
    {
        throw std::runtime_error("unable to reset vertex declaration");
    }
}

void Gx::VertexDeclaration::release()
{
    if(ptr)
    {
        ptr->Release();
        ptr = 0;
    }
}

bool Gx::VertexDeclaration::isDeviceBound() const
{
    return false;
}

WORD Gx::VertexDeclaration::size() const
{
    return sz;
}
