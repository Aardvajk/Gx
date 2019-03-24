#include "GxKeyFrame.h"

Gx::KeyFrame::KeyFrame() : position(0)
{
}

Gx::KeyFrame::KeyFrame(std::size_t count) : position(0), transforms(count)
{
}

Gx::KeyFrame Gx::Interpolator<Gx::KeyFrame>::operator()(const KeyFrame &a, const KeyFrame &b, float t) const
{
    if(t < 0) return a;
    if(t > 1) return b;

    auto r = a;
    r.position = Interpolator<float>()(a.position, b.position, t);

    for(std::size_t i = 0; i < a.transforms.size(); ++i)
    {
        r.transforms[i] = Interpolator<JointTransform>()(a.transforms[i], b.transforms[i], t);
    }

    return r;
}
