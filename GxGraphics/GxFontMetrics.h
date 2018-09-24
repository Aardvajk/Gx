#ifndef GXFONTMETRICS_H
#define GXFONTMETRICS_H

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

#endif // GXFONTMETRICS_H
