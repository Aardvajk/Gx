#ifndef GXGRAPHICSDEVICE_H
#define GXGRAPHICSDEVICE_H

#include <GxCore/GxWindows.h>

#include <GxGraphics/GxDisplaySettings.h>

#include <pcx/non_copyable.h>
#include <pcx/aligned_store.h>

#include <type_traits>

class IDirect3D9;
class IDirect3DDevice9;

namespace Gx
{

class VertexDeclaration;
class VertexBuffer;
class AbstractShader;
class VertexShader;
class PixelShader;
class VertexBuffer;

class Color;

class GraphicsDevice : public pcx::non_copyable
{
public:
    explicit GraphicsDevice(HWND hwnd, const DisplaySettings &settings);
    ~GraphicsDevice();

    void reset(const DisplaySettings &settings);
    void reset();
    
    void setVertexDeclaration(const VertexDeclaration &resource);
    void setVertexDeclaration();

    void setVertexShader(const VertexShader &resource);
    void setVertexShader();
    
    void setPixelShader(const PixelShader &resource);
    void setPixelShader();

    void begin();
    void end();

    void clear(const Color &color, float z);

    void renderTriangleList(const VertexBuffer &buffer);

    bool isOk() const;
    bool isReadyToReset() const;
    
private:
    friend class VertexDeclaration;
    friend class VertexBuffer;
    friend class AbstractShader;
    friend class Font;

    HWND hw;

    IDirect3D9 *direct3d;
    IDirect3DDevice9 *device;
    
    DisplaySettings currentSettings;
    
    pcx::aligned_store<40> cache;
};

}

#endif // GXGRAPHICSDEVICE_H
