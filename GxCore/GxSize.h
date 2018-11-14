#ifndef GX_SIZE_H
#define GX_SIZE_H

namespace Gx
{

template<typename T> class BasicSize
{
public:
    BasicSize() : width({ }), height({ }) { }
    BasicSize(T width, T height) : width(width), height(height) { }

    T width;
    T height;
};

using Size = BasicSize<unsigned>;
using SizeF = BasicSize<float>;

}

#endif // GX_SIZE_H
