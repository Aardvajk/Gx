#include "GxGraphics/GxVertexElement.h"

Gx::VertexElement::VertexElement()
{
    v.Stream = 0xFF;
    v.Offset = 0;
    v.Type = D3DDECLTYPE_UNUSED;
    v.Method = 0;
    v.Usage = 0;
    v.UsageIndex = 0;
}

Gx::VertexElement::VertexElement(WORD stream, WORD offset, BYTE type, BYTE usage, BYTE index)
{
    v.Stream = stream;
    v.Offset = offset;
    v.Type = type;
    v.Method = D3DDECLMETHOD_DEFAULT;
    v.Usage = usage;
    v.UsageIndex = index;
}
