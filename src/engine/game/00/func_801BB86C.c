#include "game_00.h"

/* Caller-side view: retail reads the fourth argument register in the call and
 * keeps the resolver result as a full word, so the call keeps its local view. */

MATCH s32 func_801BB86C(s16 from_x0, s16 from_x1, s16 from_y0, s16 from_y1, u8 probe_mode) {
    /* NOTE: retail's 16-byte frame slot; touching the array changes codegen. */
    s32 work[4];
    s32 value;
    /* FAKE: result pinned to v0. */
    FAKE_REG(s32, result, "v0");

    (void)work;
    value  = ((s32 (*)(s32, s32, u8, s16))Area_ReadStepHeight)(((from_x0 + from_x1) << 16) >> 1,
                                                               ((from_y0 + from_y1) << 16) >> 1, probe_mode, from_y1);
    result = 0;
    if (SP_REF(u8, 0x0u) != 0) {
        result = (value << 16) > 0x400000;
    }
    return result;
}
