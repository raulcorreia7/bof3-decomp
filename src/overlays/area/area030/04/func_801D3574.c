#include "area030_04.h"

/* Counts down the AREA030 scratch timer at +0x2E; on expiry it
 * resets the timer and the state byte, otherwise it runs the shared
 * state dispatcher. */
MATCH void func_801D3574(void) {
    FishingState* work;
    s32           val;

    work              = FISHING_STATE;
    val               = work->origin_x_2E - 0x1E;
    work->origin_x_2E = (u16)val;

    if ((s16)val < -0x45) {
        work->origin_x_2E      = 0xA0;
        work->handler_index_01 = 0;
        return;
    }

    Area_AddActor();
}
