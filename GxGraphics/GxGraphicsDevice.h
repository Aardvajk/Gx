#ifndef GXGRAPHICSDEVICE_H
#define GXGRAPHICSDEVICE_H

#include <GxCore/GxWindows.h>
#include <GxCore/GxNonCopyable.h>
#include <GxCore/GxAlignedStore.h>

#include <GxGraphics/GxDisplaySettings.h>

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

class GraphicsDevice : public NonCopyable
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

    void renderTriangleList(const VertexBuffer &buffer);

    bool isLost() const;
    bool isReadyToReset() const;
    
private:
    friend class VertexDeclaration;
    friend class VertexBuffer;
    friend class AbstractShader;

    HWND hw;

    IDirect3D9 *direct3d;
    IDirect3DDevice9 *device;
    
    DisplaySettings currentSettings;
    
    AlignedStore<sizeof(void*)*3> cache;
};

}

#endif // GXGRAPHICSDEVICE_H
