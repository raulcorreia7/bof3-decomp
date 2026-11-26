#include "area103_13.h"

MATCH void func_801F4374(void) {
    SELF(Actor)->pos.x.fixed      = TO_COORD(67);
    SELF(Actor)->pos.y.fixed      = TO_COORD(26);
    COORD_INT(SELF(Actor)->pos.z) = -0x100;
    SELF(Actor)->unk_32           = 0x80;
    SELF(Actor)->timer            = 0;
    SELF(Actor)->param.unk_0B     = 1;
    Area_CellSetPalette(85, 25);
    SELF(Actor)->header.step += 1;
}
