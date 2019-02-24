#ifndef GX_AUDIO_COMMON_H
#define GX_AUDIO_COMMON_H

#include "GxAudio/GxAudioTypes.h"

#include <dsound.h>

WAVEFORMATEX gx_detail_audio_wave_format(DWORD samplesPerSec, WORD bitsPerSample, WORD channels);
DSBUFFERDESC gx_detail_audio_buffer_desc(DWORD flags, DWORD bytes, WAVEFORMATEX *format);

DWORD gx_detail_audio_caps(Gx::Audio::Caps::Flags v);
DWORD gx_detail_audio_play(Gx::Audio::Play::Flags v);

#endif // GX_AUDIO_COMMON_H
