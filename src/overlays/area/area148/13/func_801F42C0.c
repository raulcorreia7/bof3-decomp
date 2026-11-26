#include "area148_13.h"

MATCH void func_801F42C0(void) {
    SELF(Actor)->direction        = SELF(Actor)->param.facing;
    COORD_INT(SELF(Actor)->pos.z) = (u16)COORD_INT(SELF(Actor)->pos.z) + 0xC0;
    Area_HeightSampleForward();
    SELF(Actor)->direction = (SELF(Actor)->direction + 3) & 0x7;
    func_801F45C8();
    SELF(Actor)->unk_06      = 2;
    SELF(Actor)->timer       = 80;
    SELF(Actor)->header.mode = 1;
}
