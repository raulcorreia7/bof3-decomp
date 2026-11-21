#include "engine/slus/slus.h"

/* subtracts amount from the indexed g_SndVoiceTargetVolume byte, clamping it at zero.
 */
/* func_8015D104 */
MATCH void SND_DecreaseVoiceTargetVolume(s32 slot, s32 amount) {
    u32 index;
    s8  value;

    index                         = slot & HALF_MASK;
    value                         = g_SndVoiceTargetVolume[index] - amount;
    g_SndVoiceTargetVolume[index] = value;
    if (value <= 0) {
        g_SndVoiceTargetVolume[index] = 0;
    }
}
