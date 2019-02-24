#ifndef GX_AUDIODEVICE_H
#define GX_AUDIODEVICE_H

#include <GxCore/GxWindows.h>

#include <pcx/non_copyable.h>

class IDirectSound8;
class IDirectSoundBuffer;

namespace Gx
{

class AudioDevice : pcx::non_copyable
{
public:
    explicit AudioDevice(HWND hw);
    virtual ~AudioDevice();

private:
    friend class AudioBuffer;

    IDirectSound8 *ptr;
    IDirectSoundBuffer *prim;
};

}

#endif // GX_AUDIODEVICE_H
