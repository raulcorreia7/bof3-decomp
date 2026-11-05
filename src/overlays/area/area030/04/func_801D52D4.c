#include "area030_04.h"

/* Draws a fixed frame, passes a bit selected by work byte 6 when
 * D_80145E93 is at least 3, then resets work fields and increments byte 1. */
MATCH void func_801D52D4(void) {
    FishingState* work;
    FishingState* stepped;
    u32           mask;

    func_801D9534(0x14, 0x12, 0x118, 0x13, 0);

    mask = 0;
    if (D_80145E93[0] >= 3) {
        mask = (1u << g_SpadWork->unk_06) & BYTE_MASK;
    }
    func_801D7C10(0x58, 0x28, mask);

    g_SpadWork->direction_08 = 0;
    work                     = FISHING_STATE;
    work->step_index_0A      = 0;
    stepped                  = FISHING_STATE;
    work->bounce_3C.unk_3C   = 0;
    work->step_14            = 0;
    work->step_limit_20      = 0;
    stepped->step_timer_09   = 4;
    ((u8*)g_SpadWork)[1]     = (u8)(((u8*)g_SpadWork)[1] + 1);
}
