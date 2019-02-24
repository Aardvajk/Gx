#ifndef GX_EXCLUSIVEGRAPHICSDEVICE_H
#define GX_EXCLUSIVEGRAPHICSDEVICE_H

#include <GxGraphics/GxGraphicsDevice.h>
#include <GxGraphics/GxDisplaySettings.h>

namespace Gx
{

class ExclusiveGraphicsDevice : public GraphicsDevice
{
public:
    ExclusiveGraphicsDevice(HWND hwnd, const DisplaySettings &settings);
    ~ExclusiveGraphicsDevice();

    void reset(const DisplaySettings &settings);
    void reset();

    void begin();
    void end();
    
private:
    HWND hw;
    DisplaySettings currentSettings;
};

}

#endif // GX_EXCLUSIVEGRAPHICSDEVICE_H
