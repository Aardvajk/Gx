#ifndef GXFONTMETRICS_H
#define GXFONTMETRICS_H

#include <GxCore/GxAlignedStore.h>

namespace Gx
{

class Font;

class FontMetrics
{
public:
    explicit FontMetrics(const Font &font);

    unsigned height() const;
    unsigned width(const std::string &text) const;

private:
    AlignedStore<16> cache;
};

}

#endif // GXFONTMETRICS_H
