#include "gx_audio_common.h"

#include <cstring>

WAVEFORMATEX gx_detail_audio_wave_format(DWORD samplesPerSec, WORD bitsPerSample, WORD channels)
{
    WAVEFORMATEX w;

    w.wFormatTag = WAVE_FORMAT_PCM;
    w.nSamplesPerSec = samplesPerSec;
    w.wBitsPerSample = bitsPerSample;
    w.nChannels = channels;
    w.nBlockAlign = (w.wBitsPerSample / 8) * w.nChannels;
    w.nAvgBytesPerSec = w.nSamplesPerSec * w.nBlockAlign;
    w.cbSize = 0;

    return w;
}

DSBUFFERDESC gx_detail_audio_buffer_desc(DWORD flags, DWORD bytes, WAVEFORMATEX *format)
{
    GUID guidNull;
    std::memset(&guidNull, 0, sizeof(GUID));

    DSBUFFERDESC d;

    d.dwSize = sizeof(DSBUFFERDESC);
    d.dwFlags = flags;
    d.dwBufferBytes = bytes;
    d.dwReserved = 0;
    d.lpwfxFormat = format;
    d.guid3DAlgorithm = guidNull;

    return d;
}

DWORD gx_detail_audio_caps(Gx::Audio::Caps::Flags v)
{
    DWORD r = 0;

    if(v & Gx::Audio::Caps::Flag::Volume) r |= DSBCAPS_CTRLVOLUME;
    if(v & Gx::Audio::Caps::Flag::Notify) r |= DSBCAPS_CTRLPOSITIONNOTIFY;

    return r;
}

DWORD gx_detail_audio_play(Gx::Audio::Play::Flags v)
{
    DWORD r = 0;

    if(v & Gx::Audio::Play::Flag::Loop) r |= DSBPLAY_LOOPING;

    return r;
}
