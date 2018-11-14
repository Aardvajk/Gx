#ifndef GX_APPLICATION_H
#define GX_APPLICATION_H

#include <GxCore/GxWindows.h>
#include <GxCore/GxSize.h>

#include <pcx/non_copyable.h>

namespace Gx
{

class Application : public pcx::non_copyable
{
public:
    explicit Application(const Size &size);
    
    void show();
    bool loop();

    HWND hwnd() const { return hw; }

private:
    HWND hw;
};

}

#endif // GX_APPLICATION_H
