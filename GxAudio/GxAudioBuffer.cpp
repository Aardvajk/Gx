#include "GxAudioBuffer.h"

#include "GxAudio/GxAudioDevice.h"

#include "internal/gx_common.h"
#include "internal/gx_audio_common.h"

#include <stdexcept>

namespace
{

class Cache
{
public:
    void *ptr;
    DWORD n;
};

}

Gx::AudioBuffer::AudioBuffer(AudioDevice &device, const Desc &desc) : d(desc), ptr(nullptr)
{
    cache.alloc<Cache>();

    auto format = gx_detail_audio_wave_format(d.sampleRate, d.bitsPerSample, d.channels);
    auto description = gx_detail_audio_buffer_desc(gx_detail_audio_caps(d.caps), d.bytes, &format);

    if(FAILED(device.ptr->CreateSoundBuffer(&description, &ptr, nullptr)))
    {
        throw std::runtime_error("unable to create directsound buffer");
    }
}

Gx::AudioBuffer::~AudioBuffer()
{
    gx_detail_com_ptr_release(ptr);
}

void *Gx::AudioBuffer::lock()
{
    auto &c = cache.get<Cache>();
    if(!FAILED(ptr->Lock(0, 0, &c.ptr, &c.n, nullptr, nullptr, DSBLOCK_ENTIREBUFFER)))
    {
        return c.ptr;
    }

    return nullptr;
}

void Gx::AudioBuffer::unlock()
{
    auto &c = cache.get<Cache>();
    ptr->Unlock(c.ptr, c.n, nullptr, 0);
}

void Gx::AudioBuffer::play(Audio::Play::Flags flags)
{
    ptr->SetCurrentPosition(0);
    ptr->SetVolume(DSBVOLUME_MAX);

    ptr->Play(0, 0, gx_detail_audio_play(flags));
}

void Gx::AudioBuffer::stop()
{
    ptr->Stop();
}
