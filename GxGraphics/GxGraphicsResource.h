#ifndef GXGRAPHICSRESOURCE_H
#define GXGRAPHICSRESOURCE_H

#include <GxCore/GxNonCopyable.h>

namespace Gx
{

class GraphicsDevice;

class GraphicsResource : public NonCopyable
{
public:
    GraphicsResource() = default;
    virtual ~GraphicsResource() = default;

    virtual void reset(GraphicsDevice &device) = 0;
    virtual void release() = 0;

    virtual bool isDeviceBound() const = 0;
};

}

#endif // GXGRAPHICSRESOURCE_H
