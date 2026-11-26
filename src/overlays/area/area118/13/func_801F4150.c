#include "area118_13.h"

MATCH void func_801F4150(void) {
    s16 distance;
    s32 y;

    SELF(Actor)->param.unk_0B     = COORD_INT(SELF(Actor)->pos.x);
    SELF(Actor)->pos.x.fixed      = (s32)D_801F51B0[SELF(Actor)->param.unk_0B * 2] << 16;
    y                             = (s32)D_801F51B1[SELF(Actor)->param.unk_0B * 2] << 16;
    SELF(Actor)->pos.y.fixed      = y;
    distance                      = Area_HeightSample(SELF(Actor)->pos.x.fixed, y);
    COORD_INT(SELF(Actor)->pos.z) = -distance / 2 - D_801F51B4[SELF(Actor)->param.unk_0B];
    SELF(Actor)->param.unk_0B++;
    if (SYS_TestFlag(D_80144ED0, D_801F5198[SELF(Actor)->param.unk_0B]) != 0) {
        SELF(Actor)->header.step++;
        func_801F4278();
    } else {
        SELF(Actor)->header.step = 3;
        func_801F43FC();
    }
}
