#include "GxApplication/GxApplication.h"

#include <stdexcept>
#include <memory>
#include <windowsx.h>

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

}

Gx::Application::Application(const Point &position, const Size &size) : hw(NULL)
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

    hw = CreateWindow("WINDOWCLASS", "Game", WS_DLGFRAME | WS_SYSMENU, position.x, position.y, 0, 0, NULL, NULL, wc.hInstance, NULL);

    if(!hw)
    {
        throw std::runtime_error("unable to create window");
    }

    RAWINPUTDEVICE Rid[1];
    Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
    Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
    Rid[0].dwFlags = RIDEV_INPUTSINK;
    Rid[0].hwndTarget = hw;
    RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

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

void Gx::Application::activationEvent(bool state)
{
}

void Gx::Application::rawMouseEvent(int x, int y)
{
}

void Gx::Application::keyPressedEvent(int key)
{
}

void Gx::Application::keyReleasedEvent(int key)
{
}

LRESULT CALLBACK Gx::Application::wndProc(HWND hw, UINT msg, WPARAM wParam, LPARAM lParam)
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
        if(msg == WM_INPUT)
        {
            UINT dwSize;
            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));

            LPBYTE lpb[dwSize];
            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

            RAWINPUT *raw = reinterpret_cast<RAWINPUT*>(lpb);

            if(raw->header.dwType == RIM_TYPEMOUSE)
            {
                app->rawMouseEvent(static_cast<int>(raw->data.mouse.lLastX), static_cast<int>(raw->data.mouse.lLastY));
                return true;
            }

            return false;
        }

        switch(msg)
        {
            case WM_ACTIVATE: app->activationEvent(static_cast<bool>(wParam)); return true;

            case WM_KEYDOWN: if(!(lParam & 0x40000000)) app->keyPressedEvent(static_cast<int>(wParam)); return true;
            case WM_KEYUP  : app->keyReleasedEvent(static_cast<int>(wParam)); return true;

            case WM_LBUTTONDOWN: app->keyPressedEvent(VK_LBUTTON); SetCapture(hw); return true;
            case WM_LBUTTONUP  : app->keyReleasedEvent(VK_LBUTTON); ReleaseCapture(); return true;

            case WM_RBUTTONDOWN: app->keyPressedEvent(VK_RBUTTON); SetCapture(hw); return true;
            case WM_RBUTTONUP  : app->keyReleasedEvent(VK_RBUTTON); ReleaseCapture(); return true;

            case WM_MBUTTONDOWN: app->keyPressedEvent(VK_MBUTTON); SetCapture(hw); return true;
            case WM_MBUTTONUP  : app->keyReleasedEvent(VK_MBUTTON); ReleaseCapture(); return true;

            default: break;
        }
    }

    return DefWindowProc(hw, msg, wParam, lParam);
}

