#include "GxApplication/GxApplication.h"

#include <stdexcept>
#include <memory>

namespace
{

void setClientSize(HWND hw, int width, int height)
{
    RECT r;
    GetClientRect(hw, &r);

    width -= r.right;
    height -= r.bottom;

    GetWindowRect(hw, &r);

    width += (r.right - r.left);
    height += (r.bottom - r.top);

    SetWindowPos(hw, NULL, 0, 0, width, height, SWP_NOMOVE);
}

LRESULT CALLBACK wndProc(HWND hw, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg == WM_DESTROY)
    {
        MSG m;
        while(PeekMessage(&m, NULL, WM_INPUT, WM_INPUT, PM_REMOVE));

        PostQuitMessage(0);
        return 0;
    }

    if(auto app = reinterpret_cast<Gx::Application*>(GetWindowLongPtr(hw, GWLP_USERDATA)))
    {
        switch(msg)
        {
            default: break;
        }
    }

    return DefWindowProc(hw, msg, wParam, lParam);
}

}

Gx::Application::Application(const Size &size) : hw(NULL)
{
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(WNDCLASS));

    wc.lpfnWndProc = wndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "WINDOWCLASS";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if(RegisterClass(&wc) == 0)
    {
        throw std::runtime_error("unable to register window class");
    }

    hw = CreateWindow("WINDOWCLASS", "Game", WS_DLGFRAME | WS_SYSMENU, 100, 100, 0, 0, NULL, NULL, wc.hInstance, NULL);

    if(!hw)
    {
        throw std::runtime_error("unable to create window");
    }

    setClientSize(hw, size.width, size.height);
    SetWindowLongPtr(hw, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

void Gx::Application::show()
{
    ShowWindow(hw, SW_SHOW);
}

bool Gx::Application::loop()
{
    MSG msg;
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.message != WM_QUIT;
}

void Gx::Application::close()
{
    PostMessage(hw, WM_CLOSE, 0, 0);
}

HWND Gx::Application::hwnd() const
{
    return hw;
}
