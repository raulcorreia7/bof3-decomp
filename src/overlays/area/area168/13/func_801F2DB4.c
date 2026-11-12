#include "area168_13.h"

MATCH void func_801F2DB4(void) {
    u8 i;

    for (i = 0; i < 6; i++) {
        Area_SetCellCode(16, D_801F4B30[i], 0);
    }
    Actor_Clear();
}
