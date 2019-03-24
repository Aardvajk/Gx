#ifndef GX_JOINTTRANSFORM_H
#define GX_JOINTTRANSFORM_H

#include <pcx/datastream.h>

#include <GxMaths/GxVector.h>
#include <GxMaths/GxQuaternion.h>
#include <GxMaths/GxBlendValue.h>

namespace Gx
{

class JointTransform
{
public:
    JointTransform();
    JointTransform(const Quaternion &rotation, const Vec3 &translation);

    Quaternion rotation;
    Vec3 translation;
};

template<> struct Interpolator<JointTransform>
{
    JointTransform operator()(const JointTransform &a, const JointTransform &b, float t) const;
};

}

inline pcx::data_istream &operator>>(pcx::data_istream &ds, Gx::JointTransform &v){ return ds >> v.rotation >> v.translation; }
inline pcx::data_ostream &operator<<(pcx::data_ostream &ds, const Gx::JointTransform &v){ return ds << v.rotation << v.translation; }

#endif // GX_JOINTTRANSFORM_H
