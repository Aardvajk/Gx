#ifndef GX_GRAPHICSDEVICE_H
#define GX_GRAPHICSDEVICE_H

#include <GxCore/GxWindows.h>

#include <GxMaths/GxColor.h>

#include <GxGraphics/GxGraphicsTypes.h>

#include <pcx/non_copyable.h>
#include <pcx/aligned_store.h>

class IDirect3D9;
class IDirect3DDevice9;

namespace Gx
{

class VertexDeclaration;
class VertexBuffer;
class AbstractShader;
class VertexShader;
class PixelShader;
class Texture;
class CubeMap;

class GraphicsDevice : public pcx::non_copyable
{
public:
    GraphicsDevice();
    virtual ~GraphicsDevice() = default;

    void setVertexDeclaration(const VertexDeclaration &declaration);
    void setVertexDeclaration();

    void setVertexShader(const VertexShader &shader);
    void setVertexShader();

    void setPixelShader(const PixelShader &shader);
    void setPixelShader();
    
    void setTexture(unsigned stage, const Texture &texture);
    void setTexture(unsigned stage, const CubeMap &cubeMap);
    void setTexture(unsigned stage);

    void setTextureFilter(unsigned stage, Graphics::Filter type);

    void clear(const Color &color, float z);
    void clear(float z);

    void renderTriangleList(const VertexBuffer &buffer, unsigned start, unsigned count);
    void renderLineList(const VertexBuffer &buffer, unsigned start, unsigned count);
    void renderPointList(const VertexBuffer &buffer, unsigned start, unsigned count);

    void setZBufferEnable(bool state);
    void setZWriteEnable(bool state);
    void setPointSize(float size);
    void setAlphaBlend(Graphics::AlphaBlend type);
    void setCulling(Graphics::Cull type);

    bool isOk() const;
    bool isReadyToReset() const;

protected:
    void clearCache();

    IDirect3D9 *direct3d;
    IDirect3DDevice9 *device;
    
private:
    friend class VertexDeclaration;
    friend class VertexBuffer;
    friend class IndexBuffer;
    friend class AbstractShader;
    friend class Font;
    friend class Texture;
    friend class CubeMap;
    friend class DepthStencilSurface;
    friend class RenderContext;

    pcx::aligned_store<40> cache;
};

}

#endif // GX_GRAPHICSDEVICE_H
