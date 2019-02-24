#include "GxAudioDevice.h"

#include "internal/gx_common.h"
#include "internal/gx_audio_common.h"

#include <stdexcept>

Gx::AudioDevice::AudioDevice(HWND hw) : ptr(nullptr), prim(nullptr)
{
    if(FAILED(DirectSoundCreate8(nullptr, &ptr, nullptr)))
    {
        throw std::runtime_error("unable to create directsound");
    }

    if(FAILED(ptr->SetCooperativeLevel(hw, DSSCL_PRIORITY)))
    {
        throw std::runtime_error("unable to set directsound cooperative level");
    }

    auto desc = gx_detail_audio_buffer_desc(DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME, 0, nullptr);
    if(FAILED(ptr->CreateSoundBuffer(&desc, &prim, nullptr)))
    {
        throw std::runtime_error("unable to create directsound primary buffer");
    }

    auto format = gx_detail_audio_wave_format(44100, 16, 2);
    if(FAILED(prim->SetFormat(&format)))
    {
        throw std::runtime_error("unable to set directsound primary buffer format");
    }
}

Gx::AudioDevice::~AudioDevice()
{
    gx_detail_com_ptr_release(prim);
    gx_detail_com_ptr_release(ptr);
}
