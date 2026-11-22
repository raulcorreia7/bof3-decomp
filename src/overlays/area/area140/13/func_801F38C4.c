#include "area140_13.h"

MATCH void func_801F38C4(void) {
    s16 z;

    z                             = (u16)COORD_INT(TASK(Actor)->pos.z) - 0x10;
    COORD_INT(TASK(Actor)->pos.z) = z;
    if ((z << 16) <= 0) {
        Area_CellClearPalette((s32)(s16)((u16)COORD_INT(TASK(Actor)->pos.x) + 1), (s32)(s16)((u16)COORD_INT(TASK(Actor)->pos.y) + 1));
        TASK(Actor)->header.step = 1;
    }
    func_801F3950(TASK(Actor)->direction, COORD_INT(TASK(Actor)->pos.z));
}
