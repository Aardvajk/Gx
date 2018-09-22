#ifndef GXAPPLICATION_H
#define GXAPPLICATION_H

#include <GxCore/GxWindows.h>
#include <GxCore/GxNonCopyable.h>

namespace Gx
{

class Application : public NonCopyable
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
