#include "GxKeyFrame.h"

namespace
{

Gx::JointTransform get(const std::vector<Gx::JointTransform> &v, std::size_t index)
{
    return index < v.size() ? v[index] : Gx::JointTransform();
}

}

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

    KeyFrame r;
    r.position = Interpolator<float>()(a.position, b.position, t);

    auto count = a.transforms.size() > b.transforms.size() ? a.transforms.size() : b.transforms.size();

    for(std::size_t i = 0; i < count; ++i)
    {
        r.transforms.push_back(Interpolator<JointTransform>()(get(a.transforms, i), get(b.transforms, i), t));
    }

    return r;
}

Gx::WeightedKey::WeightedKey() : weight(0)
{
}

Gx::WeightedKey::WeightedKey(const Gx::KeyFrame &key, float weight) : key(key), weight(weight)
{
}
