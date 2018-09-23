#ifndef GXSHADER_H
#define GXSHADER_H

#include <GxGraphics/GxGraphicsResource.h>

#include <cstdint>
#include <vector>
#include <string>
#include <map>

class IUnknown;
class ID3DXConstantTable;

#include <d3dx9.h>

namespace Gx
{

class Matrix;

class AbstractShader : public GraphicsResource
{
public:
    virtual ~AbstractShader();

    virtual void reset(GraphicsDevice &device) override;
    virtual void release() override;

    virtual bool isDeviceBound() const override;

    void setMatrix(GraphicsDevice &device, const std::string &name, const Matrix &matrix);

protected:
    enum class Type : std::uint8_t
    {
        Vertex,
        Pixel
    };

    AbstractShader(Type type, std::vector<char> buffer) : type(type), buffer(std::move(buffer)), ptr(nullptr), table(nullptr) { }

private:
    friend class GraphicsDevice;

    Type type;

    std::vector<char> buffer;

    IUnknown *ptr;
    ID3DXConstantTable *table;
};

class VertexShader : public AbstractShader
{
public:
    explicit VertexShader(std::vector<char> buffer) : AbstractShader(AbstractShader::Type::Vertex, std::move(buffer)) { }
};

class PixelShader : public AbstractShader
{
public:
    explicit PixelShader(std::vector<char> buffer) : AbstractShader(AbstractShader::Type::Pixel, std::move(buffer)) { }
};

}

#endif // GXSHADER_H
