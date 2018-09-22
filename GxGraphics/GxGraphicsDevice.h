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
    
    void begin();
    void end();

private:
    Gx::Private<sizeof(void*)*3> p;
};

}

#endif // GXGRAPHICSDEVICE_H
