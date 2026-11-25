#include "engine/slus/slus.h"

/* adds amount to the voice's pan position and derives its clamped target pan from it.
 */
MATCH void SND_VoicePanRaise(s32 voice, s32 amount) {
    u32  index;
    u16* target_pan_slot;
    s16  position;
    s16  target_pan;

    index                        = voice & HALF_MASK;
    position                     = g_SndVoicePanPosition[index] + amount;
    g_SndVoicePanPosition[index] = position;
    target_pan_slot              = &g_SndVoiceTargetPan[index];
    target_pan                   = 0x7F - (position - 0x20) / 2;
    *target_pan_slot             = target_pan;
    if (target_pan <= 0) {
        *target_pan_slot = 0;
    }
}
