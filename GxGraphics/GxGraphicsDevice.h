#ifndef GXGRAPHICSDEVICE_H
#define GXGRAPHICSDEVICE_H

#include "GxCore/GxPrivate.h"

namespace Gx
{

class GraphicsDevice
{
public:
    GraphicsDevice(void *hwnd);
    ~GraphicsDevice();

    void reset();
    
    void begin();
    void end();

    bool isLost() const;
    bool isReadyToReset() const;

private:
    Gx::Private<sizeof(void*)*3> p;
};

}

#endif // GXGRAPHICSDEVICE_H
