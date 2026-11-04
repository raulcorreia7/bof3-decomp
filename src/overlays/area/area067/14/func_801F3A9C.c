#include "area067_14.h"

/* Finds the first row of the 14-byte work table whose halfword at +0xC is zero. */
MATCH s16* func_801F3A9C(void) {
    s16* row;
    u8   i;

    row = MEM_PTR(s16, AREA_WORK_WINDOW_ADDRESS);
    for (i = 0; i < 128; i++) {
        if (row[6] == 0) {
            return row;
        }
        row += 7;
    }
    return NULL;
}
