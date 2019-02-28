#ifndef GX_SHADER_H
#define GX_SHADER_H

#include <GxGraphics/GxGraphicsResource.h>

#include <pcx/aligned_store.h>

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
    virtual ~AbstractShader() override;

    virtual void reset(GraphicsDevice &device) override;
    virtual void release() override;

    virtual bool isDeviceBound() const override;

    void reset(GraphicsDevice &device, std::vector<char> data);

    void setFloat(GraphicsDevice &device, const std::string &name, float value);
    void setVector(GraphicsDevice &device, const std::string &name, const Vec3 &value);
    void setVector(GraphicsDevice &device, const std::string &name, const Vec4 &value);
    void setMatrix(GraphicsDevice &device, const std::string &name, const Matrix &value);

protected:
    enum class Type : std::uint8_t
    {
        Vertex,
        Pixel
    };

    AbstractShader(Type type);
    AbstractShader(GraphicsDevice &device, Type type, std::vector<char> buffer);

private:
    friend class GraphicsDevice;

    Type type;

    std::vector<char> buffer;

    IUnknown *ptr;
    ID3DXConstantTable *table;
    
    pcx::aligned_store<48> cache;
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

#endif // GX_SHADER_H
