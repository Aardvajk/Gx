#include "GxGraphics/GxFont.h"

#include "GxGraphics/GxGraphicsDevice.h"

#include "GxMaths/GxColor.h"

#include "internal/gx_common.h"

#include <stdexcept>
#include <d3dx9.h>

Gx::Font::Font(GraphicsDevice &device, const Desc &desc) : d(desc), ptr(nullptr)
{
    reset(device);
}

Gx::Font::~Font()
{
    release();
}

void Gx::Font::reset(GraphicsDevice &device)
{
    release();

    HRESULT r = D3DXCreateFont(device.device, d.pointSize, 0, d.flags & Flag::Bold ? FW_BOLD : FW_NORMAL, 1, d.flags & Flag::Italic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, d.family.c_str(), &ptr);
    if(FAILED(r))
    {
        release();
        throw std::runtime_error("unable to create font");
    }

}

void Gx::Font::release()
{
    gx_detail_com_ptr_release(ptr);
}

bool Gx::Font::isDeviceBound() const
{
    return true;
}

void Gx::Font::reset(GraphicsDevice &device, const Desc &desc)
{
    d = desc;
    reset(device);
}

void Gx::Font::draw(int x, int y, const std::string &text, const Color &color)
{
    RECT rect;
    SetRect(&rect, x, y, 0, 0);

    ptr->DrawText(NULL, text.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, color);
}
