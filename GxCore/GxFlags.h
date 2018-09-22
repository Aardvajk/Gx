#ifndef GXFLAGS_H
#define GXFLAGS_H

#include <type_traits>
#include <initializer_list>

namespace Gx
{

template<typename T> class Flags
{
public:
    using type = typename std::underlying_type<T>::type;

    Flags() : v(0) { }
    Flags(T v) : v(static_cast<type>(v)) { }
    Flags(std::initializer_list<T> vs) : v(0) { for(auto i: vs) v |= static_cast<type>(i); }

    operator bool() const { return v; }
    operator T() const { return static_cast<T>(v); }

    Flags operator~() const { return static_cast<T>(~v); }

    Flags &operator|=(Flags f){ v |= f.v; return *this; }
    Flags &operator&=(Flags f){ v &= f.v; return *this; }
    Flags &operator^=(Flags f){ v ^= f.v; return *this; }

private:
    type v;
};

}

template<typename T> struct gx_detail_is_flag_enum : std::false_type { };

#define GX_DECLARE_FLAGS(T, F) using F = Gx::Flags<T>; template<> struct gx_detail_is_flag_enum<T> : std::true_type { }

template<typename T> using gx_detail_flag_type = typename std::enable_if<gx_detail_is_flag_enum<T>::value, T>::type;

template<typename T> Gx::Flags<gx_detail_flag_type<T> > operator|(T a, T b){ return T(static_cast<typename Gx::Flags<gx_detail_flag_type<T> >::type>(a) | static_cast<typename Gx::Flags<gx_detail_flag_type<T> >::type>(b)); }
template<typename T> Gx::Flags<gx_detail_flag_type<T> > operator&(T a, T b){ return T(static_cast<typename Gx::Flags<gx_detail_flag_type<T> >::type>(a) & static_cast<typename Gx::Flags<gx_detail_flag_type<T> >::type>(b)); }
template<typename T> Gx::Flags<gx_detail_flag_type<T> > operator^(T a, T b){ return T(static_cast<typename Gx::Flags<gx_detail_flag_type<T> >::type>(a) ^ static_cast<typename Gx::Flags<gx_detail_flag_type<T> >::type>(b)); }

template<typename T> Gx::Flags<gx_detail_flag_type<T> > operator~(T a){ return static_cast<T>(~static_cast<typename Gx::Flags<gx_detail_flag_type<T> >::type>(a)); }

template<typename T> Gx::Flags<T> operator|(Gx::Flags<T> a,Gx:: Flags<T> b){ return static_cast<T>(a) | static_cast<T>(b); }
template<typename T> Gx::Flags<T> operator&(Gx::Flags<T> a, Gx::Flags<T> b){ return static_cast<T>(a) & static_cast<T>(b); }
template<typename T> Gx::Flags<T> operator^(Gx::Flags<T> a, Gx::Flags<T> b){ return static_cast<T>(a) ^ static_cast<T>(b); }

template<typename T> Gx::Flags<gx_detail_flag_type<T> > operator|(T a, Gx::Flags<T> b){ return a | static_cast<T>(b); }
template<typename T> Gx::Flags<gx_detail_flag_type<T> > operator&(T a, Gx::Flags<T> b){ return a & static_cast<T>(b); }
template<typename T> Gx::Flags<gx_detail_flag_type<T> > operator^(T a, Gx::Flags<T> b){ return a ^ static_cast<T>(b); }

template<typename T> Gx::Flags<gx_detail_flag_type<T> > operator|(Gx::Flags<T> a, T b){ return static_cast<T>(a) | b; }
template<typename T> Gx::Flags<gx_detail_flag_type<T> > operator&(Gx::Flags<T> a, T b){ return static_cast<T>(a) & b; }
template<typename T> Gx::Flags<gx_detail_flag_type<T> > operator^(Gx::Flags<T> a, T b){ return static_cast<T>(a) ^ b; }

#endif // GXFLAGS_H
