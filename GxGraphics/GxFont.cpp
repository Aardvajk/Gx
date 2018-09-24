#include "GxFont.h"

#include "GxGraphics/GxGraphicsDevice.h"

#include "GxMaths/GxColor.h"

#include "internal/gx_common.h"

#include <stdexcept>
#include <d3dx9.h>

namespace
{

class Cache
{
public:
    Cache() : space(0) { }

    LONG height;
    unsigned space;
};

unsigned calculateWidth(const std::string &text, ID3DXFont *ptr, int space)
{
    unsigned trailing = 0;
    for(int i = text.length() - 1; i >= 0 && text[i] == ' '; --i)
    {
        ++trailing;
    }

    RECT rect;
    ptr->DrawText(NULL, text.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP | DT_CALCRECT | DT_SINGLELINE, 0);

    return (rect.right - rect.left) + (trailing * space);
}

}

Gx::Font::Font(GraphicsDevice &device, const Desc &desc) : d(desc), ptr(nullptr)
{
    cache.alloc<Cache>();
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

    TEXTMETRIC tm;
    ptr->GetTextMetrics(&tm);

    cache.get<Cache>().height = tm.tmHeight;
    cache.get<Cache>().space = calculateWidth("x x", ptr, 0) - calculateWidth("xx", ptr, 0);
}

void Gx::Font::release()
{
    gx_detail_com_ptr_release(ptr);
}

bool Gx::Font::isDeviceBound() const
{
    return true;
}

void Gx::Font::draw(int x, int y, const std::string &text, const Color &color)
{
    RECT rect;
    SetRect(&rect, x, y, 0, 0);

    ptr->DrawText(NULL, text.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, color);
}

unsigned Gx::Font::height() const
{
    return cache.get<Cache>().height;
}

unsigned Gx::Font::width(const std::string &text) const
{
    return ptr ? calculateWidth(text, ptr, cache.get<Cache>().space) : 0;
}
