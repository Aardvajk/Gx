#ifndef GX_RANGE_H
#define GX_RANGE_H

namespace Gx
{

template<typename T> class BasicRange
{
public:
    BasicRange() : min({ }), max({ }) { }
    BasicRange(T min, T max) : min(min), max(max) { }

    T min;
    T max;
};

class RangeF : public BasicRange<float>
{
public:
    using BasicRange::BasicRange;
};

}

#endif // GX_RANGE_H
