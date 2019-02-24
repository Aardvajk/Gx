#ifndef GX_AUDIOBUFFER_H
#define GX_AUDIOBUFFER_H

#include <GxAudio/GxAudioTypes.h>

#include <pcx/aligned_store.h>
#include <pcx/non_copyable.h>
#include <pcx/flags.h>

#include <cstdint>

class IDirectSoundBuffer;

namespace Gx
{

class AudioDevice;

class AudioBuffer : public pcx::non_copyable
{
public:
    struct Desc
    {
        std::uint32_t bytes;
        Audio::Caps::Flags caps;
        std::uint32_t sampleRate;
        std::uint16_t bitsPerSample;
        std::uint16_t channels;
    };

    AudioBuffer(AudioDevice &device, const Desc &desc);
    virtual ~AudioBuffer();

    void *lock();
    void unlock();

    void play(Audio::Play::Flags flags);
    void stop();

    IDirectSoundBuffer *buffer() const { return ptr; }

private:
    Desc d;
    IDirectSoundBuffer *ptr;

    pcx::aligned_store<16> cache;
};

}

#endif // GX_AUDIOBUFFER_H
