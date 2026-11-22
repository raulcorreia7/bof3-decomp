#include "area148_13.h"

MATCH void func_801F45C8(void) {
    TASK(Actor)->vx = g_FacingOffsets[TASK(Actor)->direction].x << 1;
    TASK(Actor)->vy = g_FacingOffsets[TASK(Actor)->direction].y << 1;
}
