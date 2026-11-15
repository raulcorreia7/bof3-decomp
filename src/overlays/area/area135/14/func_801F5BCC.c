#include "area135_14.h"

/* Sets the work record's vertical speed for a move to height and returns it;
 * the step count scales with the distance. */
MATCH s32 func_801F5BCC(s16 height) {
    s16 dy;
    s32 step;

    dy            = height - g_Task->pos.z.part.integer;
    step          = dy / 0x80;
    g_Task->timer = ABS(step) * 0x10;
    g_Task->vy    = 0;
    g_Task->vx    = 0;
    g_Task->vz    = dy / g_Task->timer;
    return g_Task->vz;
}
