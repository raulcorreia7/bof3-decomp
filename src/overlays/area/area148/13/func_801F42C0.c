#include "area148_13.h"

MATCH void func_801F42C0(void) {
    TASK(Actor)->direction        = TASK(Actor)->param.facing;
    COORD_INT(TASK(Actor)->pos.z) = (u16)COORD_INT(TASK(Actor)->pos.z) + 0xC0;
    Area_HeightSampleForward();
    TASK(Actor)->direction = (TASK(Actor)->direction + 3) & 0x7;
    func_801F45C8();
    TASK(Actor)->unk_06      = 2;
    TASK(Actor)->timer       = 80;
    TASK(Actor)->header.mode = 1;
}
