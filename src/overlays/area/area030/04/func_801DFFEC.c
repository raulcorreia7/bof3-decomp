#include "area030_04.h"

/* Writes the scratchpad work-object fields at 0x0C and 0x10 from the words at 0x34 and 0x38. */
MATCH void func_801DFFEC(void) {
    u32* record;
    u32  x;
    u32  y;

    record                       = (u32*)g_Task;
    x                            = record[13];
    y                            = record[14];
    FISHING_STATE->step_timer_09 = 8;
    record[3]                    = ((x & 0xFFFF8000u) - x) >> 3;
    record[4]                    = ((y & 0xFFFF8000u) - y) >> 3;
    FISHING_STATE->mode_index_02 += 1;
}
