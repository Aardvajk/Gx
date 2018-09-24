#include "GxGraphics/GxFontMetrics.h"

#include "GxGraphics/GxFont.h"

#include <d3dx9.h>

namespace
{

class Cache
{
public:
    explicit Cache(ID3DXFont *font) : font(font), space(0) { }

    ID3DXFont *font;
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

Gx::FontMetrics::FontMetrics(const Font &font)
{
    cache.alloc<Cache>(font.ptr);

    TEXTMETRIC tm;
    font.ptr->GetTextMetrics(&tm);

    cache.get<Cache>().height = tm.tmHeight;
    cache.get<Cache>().space = calculateWidth("x x", font.ptr, 0) - calculateWidth("xx", font.ptr, 0);
}

unsigned Gx::FontMetrics::height() const
{
    return cache.get<Cache>().height;
}

unsigned Gx::FontMetrics::width(const std::string &text) const
{
    return calculateWidth(text, cache.get<Cache>().font, cache.get<Cache>().space);
}
