#ifndef GXGRAPHICSDEVICE_H
#define GXGRAPHICSDEVICE_H

#include <GxCore/GxWindows.h>
#include <GxCore/GxNonCopyable.h>

#include <GxGraphics/GxDisplaySettings.h>

class IDirect3D9;
class IDirect3DDevice9;

namespace Gx
{

class GraphicsDevice : public NonCopyable
{
public:
    explicit GraphicsDevice(HWND hwnd, const DisplaySettings &settings);
    ~GraphicsDevice();

    void reset(const DisplaySettings &settings);
    void reset();
    
    void begin();
    void end();

    bool isLost() const;
    bool isReadyToReset() const;

private:
    friend class VertexDeclaration;

    HWND hw;

    IDirect3D9 *direct3d;
    IDirect3DDevice9 *device;
    
    DisplaySettings currentSettings;
};

}

#endif // GXGRAPHICSDEVICE_H
