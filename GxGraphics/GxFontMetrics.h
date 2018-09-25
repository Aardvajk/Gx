#ifndef GX_FONTMETRICS_H
#define GX_FONTMETRICS_H

#include <pcx/aligned_store.h>

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
    pcx::aligned_store<16> cache;
};

}

#endif // GX_FONTMETRICS_H
