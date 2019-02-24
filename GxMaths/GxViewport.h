#ifndef GX_VIEWPORT_H
#define GX_VIEWPORT_H

#include <d3d9.h>

#include <GxMaths/GxSize.h>
#include <GxMaths/GxRange.h>

namespace Gx
{

class Viewport : public D3DVIEWPORT9
{
public:
    Viewport() = default;
    explicit Viewport(const SizeF &s, const RangeF &r = { 0, 1 });
};

}

#endif // GX_VIEWPORT_H
