#ifndef GXCOLOR_H
#define GXCOLOR_H

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

    Color interpolate(const Color &v, float t) const { return (a * (1.0f - t)) + (b * t); }
};

}

#endif // GXCOLOR_H
