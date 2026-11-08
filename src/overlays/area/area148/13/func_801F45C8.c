#include "area148_13.h"

MATCH void func_801F45C8(void) {
    u8* work;

    work                   = (u8*)g_Task;
    FIELD(s32, work, 0x0C) = g_FacingOffsets[work[8]].x << 1;
    FIELD(s32, work, 0x10) = g_FacingOffsets[work[8]].y << 1;
}
