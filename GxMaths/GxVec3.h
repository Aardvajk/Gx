#ifndef GXVEC3_H
#define GXVEC3_H

#include <initializer_list>
#include <d3dx9.h>

namespace Gx
{

class Vec3 : public D3DXVECTOR3
{
public:
    using D3DXVECTOR3::D3DXVECTOR3;
};

}

#endif // GXVEC3_H
