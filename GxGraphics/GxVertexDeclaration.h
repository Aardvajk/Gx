#ifndef GXVERTEXDECLARATION_H
#define GXVERTEXDECLARATION_H

#include <GxGraphics/GxGraphicsResource.h>

#include <cstdint>
#include <vector>

class IDirect3DVertexDeclaration9;

namespace Gx
{

enum class VertexElement : std::uint8_t
{
    Position,
    Normal,
    Color,
    TexCoord
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
