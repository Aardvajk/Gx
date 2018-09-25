#ifndef GX_GRAPHICSRESOURCE_H
#define GX_GRAPHICSRESOURCE_H

#include <pcx/non_copyable.h>

namespace Gx
{

class GraphicsDevice;

class GraphicsResource : public pcx::non_copyable
{
public:
    GraphicsResource() = default;
    virtual ~GraphicsResource() = default;

    virtual void reset(GraphicsDevice &device) = 0;
    virtual void release() = 0;

    virtual bool isDeviceBound() const = 0;
};

}

#endif // GX_GRAPHICSRESOURCE_H
