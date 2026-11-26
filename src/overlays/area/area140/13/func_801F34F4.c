#include "area140_13.h"

MATCH void func_801F34F4(void) {
    s16 height;

    height                        = (u16)COORD_INT(SELF(Actor)->pos.z) + 0x10;
    COORD_INT(SELF(Actor)->pos.z) = height;
    if (height >= 128) {
        Area_CellSetPalette((s32)COORD_INT(SELF(Actor)->pos.x), (s32)COORD_INT(SELF(Actor)->pos.y));
        Area_CellClearPalette((s32)(s16)((u16)COORD_INT(SELF(Actor)->pos.x) + 1), (s32)(s16)((u16)COORD_INT(SELF(Actor)->pos.y) + 1));
        SELF(Actor)->header.step += 1;
    }
    func_801F3950(SELF(Actor)->direction, COORD_INT(SELF(Actor)->pos.z));
}
