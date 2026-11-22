#include "area030_04.h"

/* While the scratchpad work-object gate byte is set, decrements it
 * and integrates the object's three velocity components into its three
 * position accumulators. */
/* func_801E0394 */
MATCH void Fishing_MoveFish(void) {
    FishingState* work;

    if (g_Task->timer != 0) {
        g_Task->timer = (u8)(g_Task->timer - 1u);
        work          = TASK(FishingState);
        work->motion.unk_34 += work->pos_x;
        work->y_38.pos_y += work->cursor_10;
        work->bounce.half.key = (u16)(work->bounce.half.key + work->step_14);
    }
}
