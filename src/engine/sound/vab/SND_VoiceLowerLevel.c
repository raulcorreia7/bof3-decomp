#include "engine/slus/slus.h"

/* subtracts amount from the voice's pan position and derives its clamped target pan from it.
 */
MATCH void SND_VoiceLowerLevel(s32 voice, s32 amount) {
    u32  index;
    u16* level_ptr;
    s16  value;
    s16  level;

    index                        = voice & HALF_MASK;
    value                        = g_SndVoicePanPosition[index] - amount;
    g_SndVoicePanPosition[index] = value;
    level_ptr                    = &g_SndVoiceTargetPan[index];
    level                        = 0x7F - (value - 0x20) / 2;
    *level_ptr                   = level;
    if (level >= 127) {
        *level_ptr = 0;
    }
}
