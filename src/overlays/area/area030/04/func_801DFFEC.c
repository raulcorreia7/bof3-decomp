#include "area030_04.h"

/* Writes the scratchpad work-object fields at 0x0C and 0x10 from the
 * words at 0x34 and 0x38: each becomes (word & 0xFFFF8000) - word, i.e. the
 * negated low 15 bits, shifted right 3. Also marks byte 0x09 as 8 and bumps
 * the work-object step byte 0x02. */
MATCH void func_801DFFEC(void) {
    u32* record;
    u32  x;
    u32  y;

    record             = (u32*)g_SpadWork;
    x                  = record[13];
    y                  = record[14];
    FISHING_STATE->step_timer_09 = 8;
    record[3]          = ((x & 0xFFFF8000u) - x) >> 3;
    record[4]          = ((y & 0xFFFF8000u) - y) >> 3;
    FISHING_STATE->mode_index_02 += 1;
}
