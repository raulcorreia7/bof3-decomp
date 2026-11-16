#include "area067_14.h"

/* The group header types this name's three-argument form; the step reads none. */
MATCH void func_801F39D8(s32 x, s32 y, u32 sprite_id) {
    s16* row;
    u8   i;

    row = MEM_PTR(s16, AREA_WORK);
    for (i = 0; i < 128; i++) {
        if (row[6] != 0) {
            func_801F38A0(row);
            row[1] -= row[3];
            row[3] += row[6] & 1;
            row[2] += 1;
            if (--row[6] == 0) {
                func_801F3D54(row);
            }
        }
        row += 7;
    }
}
