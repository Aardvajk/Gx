#ifndef GX_APPLICATION_H
#define GX_APPLICATION_H

#include <GxCore/GxWindows.h>

#include <GxMaths/GxPoint.h>
#include <GxMaths/GxSize.h>

#include <pcx/non_copyable.h>

namespace Gx
{

class Application : public pcx::non_copyable
{
public:
    explicit Application(const Point &position, const Size &size);
    virtual ~Application() = default;
    
    void show();
    bool loop();

    void close();

    HWND hwnd() const;

protected:
    virtual void activationEvent(bool state);
    virtual void rawMouseEvent(int x, int y);
    virtual void keyPressedEvent(int key);
    virtual void keyReleasedEvent(int key);

private:
    static LRESULT CALLBACK wndProc(HWND hw, UINT msg, WPARAM wParam, LPARAM lParam);

    HWND hw;
};

}

#endif // GX_APPLICATION_H
