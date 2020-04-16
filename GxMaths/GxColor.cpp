#include "GxMaths/GxColor.h"

namespace
{

float convert(int v)
{
    return static_cast<float>(v) / 255;
}

}

Gx::Color Gx::Color::fromInts(int r, int g, int b, int a)
{
    return Color(convert(r), convert(g), convert(b), convert(a));
}
