#include "area148_13.h"

MATCH void func_801F45C8(void) {
    SELF(Actor)->vx = g_FacingOffsets[SELF(Actor)->direction].x << 1;
    SELF(Actor)->vy = g_FacingOffsets[SELF(Actor)->direction].y << 1;
}
