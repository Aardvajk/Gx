#ifndef GXSHADER_H
#define GXSHADER_H

#include <GxCore/GxAlignedStore.h>

#include <GxGraphics/GxGraphicsResource.h>

#include <cstdint>
#include <vector>

class IUnknown;
class ID3DXConstantTable;

namespace Gx
{

class Vec3;
class Vec4;
class Matrix;

class AbstractShader : public GraphicsResource
{
public:
    virtual ~AbstractShader();

    virtual void reset(GraphicsDevice &device) override;
    virtual void release() override;

    virtual bool isDeviceBound() const override;

    void setVector(GraphicsDevice &device, const std::string &name, const Vec3 &value);
    void setVector(GraphicsDevice &device, const std::string &name, const Vec4 &value);
    void setMatrix(GraphicsDevice &device, const std::string &name, const Matrix &value);

protected:
    enum class Type : std::uint8_t
    {
        Vertex,
        Pixel
    };

    AbstractShader(GraphicsDevice &device, Type type, std::vector<char> buffer);

private:
    friend class GraphicsDevice;

    Type type;

    std::vector<char> buffer;

    IUnknown *ptr;
    ID3DXConstantTable *table;
    
    AlignedStore<48> cache;
};

class VertexShader : public AbstractShader
{
public:
    explicit VertexShader(GraphicsDevice &device, std::vector<char> buffer) : AbstractShader(device,AbstractShader::Type::Vertex, std::move(buffer)) { }
};

class PixelShader : public AbstractShader
{
public:
    explicit PixelShader(GraphicsDevice &device, std::vector<char> buffer) : AbstractShader(device, AbstractShader::Type::Pixel, std::move(buffer)) { }
};

}

#endif // GXSHADER_H
