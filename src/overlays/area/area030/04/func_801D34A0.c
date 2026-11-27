#include "area030_04.h"

/* Counts down the AREA030 scratch timer at +0x2E; when it falls
 * below the threshold it reloads the counter pair and advances the state
 * byte, then runs the shared state dispatcher. */
MATCH void func_801D34A0(void) {
    FishingState* work;
    s32           val;
    FishingState* stepped;

    work = SELF(FishingState);

    val            = work->origin_x - 0x1E;
    work->origin_x = val;

    if ((s16)val < 0xA1) {
        work->timer            = 0x1E;
        stepped                = SELF(FishingState);
        work->origin_x         = 0xA0;
        stepped->handler_index = (stepped->handler_index + 1);
    }

    Area_AddActor();
}
