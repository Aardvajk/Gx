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
    Color(float r, float g, float b) : D3DXCOLOR(r, g, b, 1.0f) { }
};

}

#endif // GXCOLOR_H
