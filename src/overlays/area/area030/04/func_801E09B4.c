#include "area030_04.h"

/* Walks the 30 AREA030 state records (stride 0x98) and runs the
 * per-record update for each live one, publishing the active record through the
 * scratchpad pointer cell. */
MATCH void func_801E09B4(void) {
    u8* p;
    s32 i;
    s32 offset;

    i      = 0;
    /* FAKE: retail reads g_Actors as u8[]. */
    p      = ((u8*)g_Actors);
    offset = 0;
    for (; i < 30; i++) {
        /* FAKE: retail reads g_Actors as u8[]. */
        if (((u8*)g_Actors)[offset] != 0) {
            g_Task = p;
            func_801E084C();
        }
        p += 0x98;
        offset += 0x98;
    }
}
