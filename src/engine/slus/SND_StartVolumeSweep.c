#include "engine/slus/slus.h"

/* starts a volume sweep on the voice from the current level in g_SndVoiceVolume to the target level in g_SndVoiceTargetVolume. */
MATCH void SND_StartVolumeSweep(s32 voice) {
    u16 index;

    index = voice;
    SsUtAutoVol(index, g_SndVoiceVolume[index], (s8)g_SndVoiceTargetVolume[index], 1);
    g_SndVoiceVolume[index] = g_SndVoiceTargetVolume[index];
}
