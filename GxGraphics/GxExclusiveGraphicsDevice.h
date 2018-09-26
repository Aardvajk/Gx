#ifndef GXEXCLUSIVEGRAPHICSDEVICE_H
#define GXEXCLUSIVEGRAPHICSDEVICE_H

#include <GxGraphics/GxGraphicsDevice.h>
#include <GxGraphics/GxDisplaySettings.h>

namespace Gx
{

class ExclusiveGraphicsDevice : public GraphicsDevice
{
public:
    explicit ExclusiveGraphicsDevice(HWND hwnd, const DisplaySettings &settings);
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

#endif // GXEXCLUSIVEGRAPHICSDEVICE_H
