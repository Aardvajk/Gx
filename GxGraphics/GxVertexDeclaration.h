#ifndef GXVERTEXDECLARATION_H
#define GXVERTEXDECLARATION_H

#include <GxGraphics/GxGraphicsResource.h>

#include <cstdint>
#include <vector>

class IDirect3DVertexDeclaration9;

namespace Gx
{

class VertexElement
{
public:
    enum class Type : std::uint8_t
    {
        Position,
        Normal,
        Color,
        TexCoord
    };

    VertexElement() = default;
    VertexElement(Type type, std::uint8_t index = 0) : type(type), index(index) { }

    Type type;
    std::uint8_t index;
};

class VertexDeclaration : public GraphicsResource
{
public:
    explicit VertexDeclaration(std::vector<VertexElement> elements);
    virtual ~VertexDeclaration();

    virtual void reset(GraphicsDevice &device) override;
    virtual void release() override;

    virtual bool isDeviceBound() const override;
    
    std::uint16_t stride() const;

private:
    friend class GraphicsDevice;

    IDirect3DVertexDeclaration9 *ptr;
    std::vector<VertexElement> elements;
    std::uint16_t str;
};

}
#endif // GXVERTEXDECLARATION_H
