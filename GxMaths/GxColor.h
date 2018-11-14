#ifndef GX_COLOR_H
#define GX_COLOR_H

#include <d3dx9.h>

namespace Gx
{

using Rgba = D3DCOLOR;

class Color : public D3DXCOLOR
{
public:
    using D3DXCOLOR::D3DXCOLOR;

    Color() = default;
    Color(float r, float g, float b) : D3DXCOLOR(r, g, b, 1.0f) { }
    Color(const D3DXCOLOR &v) : D3DXCOLOR(v) { }

    Color interpolated(const Color &v, float t) const { return (*this * (1.0f - t)) + (v * t); }
};

}

#endif // GX_COLOR_H
