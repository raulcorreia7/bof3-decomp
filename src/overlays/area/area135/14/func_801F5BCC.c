#include "area135_14.h"

/* Sets the work record's vertical speed for a move to height and returns it;
 * the step count scales with the distance. */
MATCH s32 func_801F5BCC(s16 height) {
    s16 dy;
    s32 step;

    dy                 = height - SELF(Actor)->pos.z.part.integer;
    step               = dy / 0x80;
    SELF(Actor)->timer = ABS(step) * 0x10;
    SELF(Actor)->vy    = 0;
    SELF(Actor)->vx    = 0;
    SELF(Actor)->vz    = dy / SELF(Actor)->timer;
    return SELF(Actor)->vz;
}
