#include "area140_13.h"

MATCH void func_801F38C4(void) {
    s16 z;

    z                             = (u16)COORD_INT(SELF(Actor)->pos.z) - 0x10;
    COORD_INT(SELF(Actor)->pos.z) = z;
    if ((z << 16) <= 0) {
        Area_CellClearPalette((s32)(s16)((u16)COORD_INT(SELF(Actor)->pos.x) + 1), (s32)(s16)((u16)COORD_INT(SELF(Actor)->pos.y) + 1));
        SELF(Actor)->header.step = 1;
    }
    func_801F3950(SELF(Actor)->direction, COORD_INT(SELF(Actor)->pos.z));
}
