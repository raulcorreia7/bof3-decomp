#include "area030_04.h"

#define WORLD00_FISHING_DRAW_ENABLE SP_REF(u8, 0u)

/* Holds the AREA030 fade flag: a pad-1 input bit forces the flag on
 * and refills the fade counter, otherwise a pad-2 bit drains the counter and
 * keeps the flag on until it reaches zero. */
MATCH void func_801DDEEC(void) {
    FishingState* record;

    if (g_InputPressed & PADLdown) {
        record                      = FISHING_STATE;
        WORLD00_FISHING_DRAW_ENABLE = 1;
        record->step_index_0A       = 8;
    } else if (g_InputHeld & PADLdown) {
        record = FISHING_STATE;
        if (record->step_index_0A != 0) {
            record->step_index_0A -= 1;
            WORLD00_FISHING_DRAW_ENABLE = 1;
        } else {
            WORLD00_FISHING_DRAW_ENABLE = 0;
        }
    } else {
        WORLD00_FISHING_DRAW_ENABLE = 0;
    }
}
