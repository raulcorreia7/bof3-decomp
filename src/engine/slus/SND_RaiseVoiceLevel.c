#include "engine/slus/slus.h"

/* adds amount to the D_80149070 accumulator and derives the clamped
 * D_80149040 level from it.
 */
MATCH void SND_RaiseVoiceLevel(s32 voice, s32 amount) {
    u32  index;
    u16* level_ptr;
    s16  value;
    s16  level;

    index             = voice & HALF_MASK;
    value             = D_80149070[index] + amount;
    D_80149070[index] = value;
    level_ptr         = &D_80149040[index];
    level             = 0x7F - (value - 0x20) / 2;
    *level_ptr        = level;
    if (level <= 0) {
        *level_ptr = 0;
    }
}
