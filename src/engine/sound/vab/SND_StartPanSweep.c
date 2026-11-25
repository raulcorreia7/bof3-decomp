#include "engine/slus/slus.h"

/* starts a pan sweep on the voice from its pan to its target pan, then records the target as its pan.
 */
MATCH void SND_StartPanSweep(s32 voice) {
    u16 index;

    index = voice;
    SsUtAutoPan(index, g_SndVoicePan[index], g_SndVoiceTargetPan[index], 1);
    g_SndVoicePan[index] = g_SndVoiceTargetPan[index];
}
