#ifndef GXFONT_H
#define GXFONT_H

#include <GxCore/GxFlags.h>
#include <GxCore/GxAlignedStore.h>

#include <GxGraphics/GxGraphicsResource.h>

#include <string>

class ID3DXFont;

namespace Gx
{

class Color;

class Font : public GraphicsResource
{
public:
    enum class Flag
    {
        Bold = 1,
        Italic = 2
    };

    using Flags = Gx::Flags<Flag>;

    struct Desc
    {
        int pointSize;
        std::string family;
        Flags flags;
    };

    Font(GraphicsDevice &device, const Desc &desc);
    ~Font();
    
    virtual void reset(GraphicsDevice &device) override;
    virtual void release() override;

    virtual bool isDeviceBound() const override;

    void draw(int x, int y, const std::string &text, const Color &color);
    
    unsigned height() const;
    unsigned width(const std::string &text) const;

private:
    friend class GraphicsDevice;

    Desc d;
    ID3DXFont *ptr;
    
    AlignedStore<8> cache;
};

}

template<> struct GxIsFlagEnum<Gx::Font::Flag> : std::true_type { };

#endif // GXFONT_H
