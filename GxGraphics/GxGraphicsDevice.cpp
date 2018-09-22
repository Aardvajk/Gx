#include "GxGraphics/GxGraphicsDevice.h"

#include <memory>
#include <d3d9.h>

namespace
{

D3DPRESENT_PARAMETERS
createParams(HWND hw, int width, int height)
{
    D3DPRESENT_PARAMETERS p;
    ZeroMemory(&p, sizeof(D3DPRESENT_PARAMETERS));

    p.BackBufferWidth = width;
    p.BackBufferHeight = height;

    p.BackBufferFormat = D3DFMT_X8R8G8B8;
    p.BackBufferCount = 1;

    p.MultiSampleType = D3DMULTISAMPLE_NONE;

    p.SwapEffect = D3DSWAPEFFECT_DISCARD;
    p.hDeviceWindow = hw;
    p.Windowed = true;
    p.EnableAutoDepthStencil = true;
    p.AutoDepthStencilFormat = D3DFMT_D24S8;
    p.Flags = 0;

    p.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    p.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

    return p;
}

void
setGlobalDeviceSettings(IDirect3DDevice9 *device)
{
    DWORD filter = D3DTEXF_LINEAR;

    for(int i = 0; i < 3; ++i)
    {
        device->SetSamplerState(i, D3DSAMP_MAGFILTER, filter);
        device->SetSamplerState(i, D3DSAMP_MINFILTER, filter);

        device->SetSamplerState(i, D3DSAMP_MIPFILTER, filter);

        device->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        device->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
    }

    device->SetRenderState(D3DRS_ZENABLE, true);
    device->SetRenderState(D3DRS_LIGHTING, false);
    device->SetRenderState(D3DRS_STENCILENABLE, false);

    device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
    device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
}

template<typename T> void release(T *&t){ if(t) { t->Release(); t = nullptr; } }

}

Gx::GraphicsDevice::GraphicsDevice(HWND hwnd) : hw(hwnd)
{
    direct3d = Direct3DCreate9(D3D_SDK_VERSION);
    if(!direct3d)
    {
        throw std::runtime_error("unable to create direct3D");
    }

    D3DCAPS9 caps;
    HRESULT r = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
    if(FAILED(r))
    {
        release(direct3d);
        throw std::runtime_error("unable to get device caps");
    }

    DWORD vertexProcessing;

    if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    else                                              vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

    D3DPRESENT_PARAMETERS params = createParams(hw, 640, 480);

    r = direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hw, vertexProcessing, &params, &(device));
    if(FAILED(r))
    {
        release(device);
        release(direct3d);

        throw std::runtime_error("unable to create device");
    }

    setGlobalDeviceSettings(device);
}

Gx::GraphicsDevice::~GraphicsDevice()
{
    release(device);
    release(direct3d);
}

void Gx::GraphicsDevice::reset()
{
    D3DPRESENT_PARAMETERS params = createParams(hw, 640, 480);

    HRESULT r = device->Reset(&params);
    if(FAILED(r))
    {
        release(device);
        release(direct3d);

        throw std::runtime_error("unable to reset device");
    }
}

void Gx::GraphicsDevice::begin()
{
    device->BeginScene();
    device->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 0, 0), 1, 0);
}

void Gx::GraphicsDevice::end()
{
    device->EndScene();
    device->Present(NULL, NULL, hw, NULL);
}

bool Gx::GraphicsDevice::isLost() const
{
    return device ? device->TestCooperativeLevel() == D3DERR_DEVICELOST : true;
}

bool Gx::GraphicsDevice::isReadyToReset() const
{
    return device ? device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET : false;
}
