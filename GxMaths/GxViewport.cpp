#include "GxViewport.h"

Gx::Viewport::Viewport(const SizeF &s, const RangeF &r)
{
    X = 0;
    Y = 0;

    Width = static_cast<DWORD>(s.width);
    Height = static_cast<DWORD>(s.height);

    MinZ = r.min;
    MaxZ = r.max;
}
