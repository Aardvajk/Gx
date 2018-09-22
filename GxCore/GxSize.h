#ifndef GXSIZE_H
#define GXSIZE_H

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

using Size = BasicSize<int>;
using SizeF = BasicSize<float>;

}

#endif // GXSIZE_H
