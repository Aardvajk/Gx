#ifndef GX_FONT_H
#define GX_FONT_H

#include <GxGraphics/GxGraphicsResource.h>

#include <pcx/flags.h>

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

    using Flags = pcx::flags<Flag>;

    struct Desc
    {
        int pointSize;
        std::string family;
        Flags flags;
    };

    Font();
    explicit Font(GraphicsDevice &device, const Desc &desc);
    virtual ~Font() override;
    
    virtual void reset(GraphicsDevice &device) override;
    virtual void release() override;

    virtual bool isDeviceBound() const override;

    void reset(GraphicsDevice &device, const Desc &desc);

    void draw(int x, int y, const std::string &text, const Color &color);
    
private:
    friend class GraphicsDevice;
    friend class FontMetrics;

    Desc d;
    ID3DXFont *ptr;
};

}

template<> struct pcx_is_flag_enum<Gx::Font::Flag> : std::true_type { };

#endif // GX_FONT_H
