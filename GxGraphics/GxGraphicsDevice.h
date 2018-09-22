#ifndef GXGRAPHICSDEVICE_H
#define GXGRAPHICSDEVICE_H

#include <windows.h>

class IDirect3D9;
class IDirect3DDevice9;

namespace Gx
{

class GraphicsDevice
{
public:
    GraphicsDevice(HWND hwnd);
    ~GraphicsDevice();

    void reset();
    
    void begin();
    void end();

    bool isLost() const;
    bool isReadyToReset() const;

private:
    HWND hw;

    IDirect3D9 *direct3d;
    IDirect3DDevice9 *device;
};

}

#endif // GXGRAPHICSDEVICE_H
