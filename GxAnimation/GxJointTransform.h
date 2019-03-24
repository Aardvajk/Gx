#ifndef GX_JOINTTRANSFORM_H
#define GX_JOINTTRANSFORM_H

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

#endif // GX_JOINTTRANSFORM_H
