#include "area103_13.h"

MATCH void func_801F4374(void) {
    TASK(Actor)->pos.x.fixed      = TO_COORD(67);
    TASK(Actor)->pos.y.fixed      = TO_COORD(26);
    COORD_INT(TASK(Actor)->pos.z) = -0x100;
    TASK(Actor)->unk_32           = 0x80;
    TASK(Actor)->timer            = 0;
    TASK(Actor)->param.unk_0B     = 1;
    Area_CellSetPalette(85, 25);
    TASK(Actor)->header.step += 1;
}
