#ifndef GXAPPLICATION_H
#define GXAPPLICATION_H

#include <windows.h>

namespace Gx
{

class Application
{
public:
    Application();
    
    void show();
    bool loop();

    HWND hwnd() const { return hw; }

private:
    HWND hw;
};

}

#endif // GXAPPLICATION_H
