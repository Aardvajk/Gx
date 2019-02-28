#include "GxGraphics/GxShader.h"

#include "GxGraphics/GxGraphicsDevice.h"

#include "GxMaths/GxVector.h"
#include "GxMaths/GxMatrix.h"

#include "GxCore/GxDebug.h"

#include "internal/gx_common.h"

#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <d3dx9.h>

namespace
{

class Cache
{
public:
    D3DXHANDLE handle(ID3DXConstantTable *table, const std::string &name);

    std::map<std::string, D3DXHANDLE> handles;
};

D3DXHANDLE Cache::handle(ID3DXConstantTable *table, const std::string &name)
{
    auto i = handles.find(name);
    if(i != handles.end())
    {
        return i->second;
    }

    D3DXHANDLE n = table->GetConstantByName(0, name.c_str());
    handles.insert(make_pair(name, n));

    return n;
}

}

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
        release();
        throw std::runtime_error("unable to create shader");
    }

    r = D3DXGetShaderConstantTable(reinterpret_cast<DWORD*>(buffer.data()), &table);

    if(FAILED(r))
    {
        release();
        throw std::runtime_error("unable to get shader constant table");
    }
}

void Gx::AbstractShader::release()
{
    gx_detail_com_ptr_release(table);
    gx_detail_com_ptr_release(ptr);
    
    cache.get<Cache>().handles.clear();
}

bool Gx::AbstractShader::isDeviceBound() const
{
    return false;
}

void Gx::AbstractShader::reset(GraphicsDevice &device, std::vector<char> data)
{
    buffer = std::move(data);
    reset(device);
}

void Gx::AbstractShader::setFloat(GraphicsDevice &device, const std::string &name, float value)
{
    table->SetFloat(device.device, cache.get<Cache>().handle(table, name), value);
}

void Gx::AbstractShader::setVector(GraphicsDevice &device, const std::string &name, const Vec3 &value)
{
    setVector(device, name, Vec4(value.x, value.y, value.z, 1));
}

void Gx::AbstractShader::setVector(GraphicsDevice &device, const std::string &name, const Vec4 &value)
{
    table->SetVector(device.device, cache.get<Cache>().handle(table, name), &value);
}

void Gx::AbstractShader::setMatrix(GraphicsDevice &device, const std::string &name, const Matrix &value)
{
    table->SetMatrix(device.device, cache.get<Cache>().handle(table, name), &value);
}

Gx::AbstractShader::AbstractShader(Type type) : ptr(nullptr), table(nullptr)
{
    cache.alloc<Cache>();
}

Gx::AbstractShader::AbstractShader(GraphicsDevice &device, Type type, std::vector<char> buffer) : type(type), buffer(std::move(buffer)), ptr(nullptr), table(nullptr)
{
    cache.alloc<Cache>();
    reset(device);
}
