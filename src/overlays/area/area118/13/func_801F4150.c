#include "area118_13.h"

MATCH void func_801F4150(void) {
    s16 distance;
    s32 y;

    TASK(Actor)->param.unk_0B     = COORD_INT(TASK(Actor)->pos.x);
    TASK(Actor)->pos.x.fixed      = (s32)D_801F51B0[TASK(Actor)->param.unk_0B * 2] << 16;
    y                             = (s32)D_801F51B1[TASK(Actor)->param.unk_0B * 2] << 16;
    TASK(Actor)->pos.y.fixed      = y;
    distance                      = Area_HeightSample(TASK(Actor)->pos.x.fixed, y);
    COORD_INT(TASK(Actor)->pos.z) = -distance / 2 - D_801F51B4[TASK(Actor)->param.unk_0B];
    TASK(Actor)->param.unk_0B++;
    if (SYS_TestFlag(D_80144ED0, D_801F5198[TASK(Actor)->param.unk_0B]) != 0) {
        TASK(Actor)->header.step++;
        func_801F4278();
    } else {
        TASK(Actor)->header.step = 3;
        func_801F43FC();
    }
}
