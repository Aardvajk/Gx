#ifndef GXVERTEXELEMENT_H
#define GXVERTEXELEMENT_H

#include <GxCore/GxWindows.h>

#include <d3d9.h>

namespace Gx
{

class VertexElement
{
public:
    VertexElement();
    VertexElement(WORD stream, WORD offset, BYTE type, BYTE usage, BYTE index);

private:
    D3DVERTEXELEMENT9 v;
};

}

#endif // GXVERTEXELEMENT_H
