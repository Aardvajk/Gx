#ifndef GXVERTEXDECLARATION_H
#define GXVERTEXDECLARATION_H

#include <GxGraphics/GxGraphicsResource.h>
#include <GxGraphics/GxVertexElement.h>

#include <vector>

class IDirect3DVertexDeclaration9;

namespace Gx
{

class VertexDeclaration : public GraphicsResource
{
public:
    VertexDeclaration(std::vector<VertexElement> elements, WORD size);
    virtual ~VertexDeclaration();

    virtual void reset(GraphicsDevice &device) override;
    virtual void release() override;

    virtual bool isDeviceBound() const override;

    WORD size() const;

private:
    friend class GraphicsDevice;

    IDirect3DVertexDeclaration9 *ptr;
    std::vector<VertexElement> elements;
    WORD sz;
};

}
#endif // GXVERTEXDECLARATION_H
