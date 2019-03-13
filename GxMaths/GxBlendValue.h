#ifndef GX_BLENDVALUE_H
#define GX_BLENDVALUE_H

#include <utility>

namespace Gx
{

template<typename T> struct Interpolator
{
    T operator()(const T &a, const T &b, float t) const { if(t < 0) return a; if(t > 1) return b; return (a * (1 - t)) + (b * t); }
};

template<typename T> class BlendValue
{
public:
    BlendValue(const T &t = T()) : v(t), o(v) { }
    template<typename... Args> BlendValue(Args&&... args) : v(std::forward<Args>(args)...), o(v) { }

    void store(){ o = v; }

    void set(const T &t){ v = t; }
    void add(const T &t){ v += t; }

    T value() const { return v; }
    T value(float blend) const { return Interpolator<T>()(o, v, blend); }

private:
    T v;
    T o;
};

using BlendFloat = BlendValue<float>;

}

#endif // G_XBLENDVALUE_H
