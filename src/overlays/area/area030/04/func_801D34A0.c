#include "area030_04.h"

/* Counts down the AREA030 scratch timer at +0x2E; when it falls
 * below the threshold it reloads the counter pair and advances the state
 * byte, then runs the shared state dispatcher. */
MATCH void func_801D34A0(void) {
    FishingState* work;
    s32           val;
    FishingState* stepped;

    work = FISHING_STATE;

    val               = work->origin_x_2E - 0x1E;
    work->origin_x_2E = (u16)val;

    if ((s16)val < 0xA1) {
        work->step_timer_09       = 0x1E;
        stepped                   = FISHING_STATE;
        work->origin_x_2E         = 0xA0;
        stepped->handler_index_01 = (u8)(stepped->handler_index_01 + 1);
    }

    Area_AddActor();
}
