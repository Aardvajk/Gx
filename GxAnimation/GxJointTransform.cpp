#include "GxJointTransform.h"

Gx::JointTransform::JointTransform() : rotation(Quaternion::identity()), translation(0, 0, 0)
{
}

Gx::JointTransform::JointTransform(const Quaternion &rotation, const Vec3 &translation) : rotation(rotation), translation(translation)
{
}

Gx::JointTransform Gx::Interpolator<Gx::JointTransform>::operator()(const JointTransform &a, const JointTransform &b, float t) const
{
    if(t < 0) return a;
    if(t > 1) return b;

    return JointTransform(Gx::Interpolator<Quaternion>()(a.rotation, b.rotation, t), Gx::Interpolator<Vec3>()(a.translation, b.translation, t));
}
