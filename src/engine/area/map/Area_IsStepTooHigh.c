#include "engine/game/00/game_00.h"

/* Caller-side view: retail reads the fourth argument register in the call and
 * keeps the resolver result as a full word, so the call keeps its local view. */

MATCH s32 Area_IsStepTooHigh(s16 from_x0, s16 from_x1, s16 from_y0, s16 from_y1, u8 probe_mode) {
    /* 16-byte frame slot the body never reads; a smaller one changes the bytes. */
    s32 work[4];
    s32 value;

    (void)work;
    value = ((s32 (*)(s32, s32, u8, s16))Area_HeightReadStep)(((from_x0 + from_x1) << 16) >> 1, ((from_y0 + from_y1) << 16) >> 1, probe_mode, from_y1);
    if (SP_REF(u8, 0x0u) != 0 && (value << 16) > 0x400000) {
        return 1;
    }
    return 0;
}
