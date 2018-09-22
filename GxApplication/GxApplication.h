#ifndef GXAPPLICATION_H
#define GXAPPLICATION_H

#include "GxCore/GxPrivate.h"

namespace Gx
{

class Application
{
public:
    Application();
    
    void show();
    bool loop();

    void *hwnd() const;

private:
    Gx::Private<sizeof(void*)> p;
};

}

#endif // GXAPPLICATION_H
