#include "GxExclusiveGraphicsDevice.h"

#include "internal/gx_common.h"

#include <d3d9.h>

namespace
{

D3DPRESENT_PARAMETERS
createParams(HWND hw, const Gx::DisplaySettings &settings)
{
    D3DPRESENT_PARAMETERS p;
    ZeroMemory(&p, sizeof(D3DPRESENT_PARAMETERS));

    p.BackBufferWidth = settings.size.width;
    p.BackBufferHeight = settings.size.height;

    p.BackBufferFormat = D3DFMT_X8R8G8B8;
    p.BackBufferCount = 1;

    p.MultiSampleType = D3DMULTISAMPLE_NONE;

    p.SwapEffect = D3DSWAPEFFECT_DISCARD;
    p.hDeviceWindow = hw;
    p.Windowed = settings.options & Gx::DisplaySettings::Flag::Windowed;
    p.EnableAutoDepthStencil = true;
    p.AutoDepthStencilFormat = D3DFMT_D24S8;
    p.Flags = 0;

    p.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    p.PresentationInterval = settings.options & Gx::DisplaySettings::Flag::VSync ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;

    return p;
}

DWORD vertexProcessing(bool hardware)
{
    return hardware ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;
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

void resetDevice(IDirect3D9 *&direct3d, IDirect3DDevice9 *&device, HWND hw, const Gx::DisplaySettings &settings)
{
    D3DPRESENT_PARAMETERS params = createParams(hw, settings);

    if(FAILED(device->Reset(&params)))
    {
        gx_detail_com_ptr_release(device);
        gx_detail_com_ptr_release(direct3d);

        throw std::runtime_error("unable to reset device");
    }

    setGlobalDeviceSettings(device);
}

}

Gx::ExclusiveGraphicsDevice::ExclusiveGraphicsDevice(HWND hwnd, const DisplaySettings &settings) : hw(hwnd), currentSettings(settings)
{
    direct3d = Direct3DCreate9(D3D_SDK_VERSION);
    if(!direct3d)
    {
        throw std::runtime_error("unable to create direct3D");
    }

    D3DCAPS9 caps;
    
    if(FAILED(direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
    {
        gx_detail_com_ptr_release(direct3d);
        throw std::runtime_error("unable to get device caps");
    }

    D3DPRESENT_PARAMETERS params = createParams(hw, currentSettings);

    if(FAILED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hw, vertexProcessing(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT), &params, &(device))))
    {
        gx_detail_com_ptr_release(device);
        gx_detail_com_ptr_release(direct3d);

        throw std::runtime_error("unable to create device");
    }

    setGlobalDeviceSettings(device);
}

Gx::ExclusiveGraphicsDevice::~ExclusiveGraphicsDevice()
{
    gx_detail_com_ptr_release(device);
    gx_detail_com_ptr_release(direct3d);
}

void Gx::ExclusiveGraphicsDevice::reset(const DisplaySettings &settings)
{
    resetDevice(direct3d, device, hw, settings);
    currentSettings = settings;

    clearCache();
}

void Gx::ExclusiveGraphicsDevice::reset()
{
    resetDevice(direct3d, device, hw, currentSettings);
    clearCache();
}

void Gx::ExclusiveGraphicsDevice::begin()
{
    device->BeginScene();
}

void Gx::ExclusiveGraphicsDevice::end()
{
    device->EndScene();
    device->Present(NULL, NULL, hw, NULL);
}

