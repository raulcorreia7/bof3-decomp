#include "area059_13.h"

MATCH void func_801F3060(void) {
    Actor* work;
    s32    pos[3];

    work   = SP_REF(Actor*, 0x44);
    pos[0] = work->pos.x.fixed;
    pos[1] = work->pos.y.fixed;
    pos[2] = work->pos.z.fixed;
    Area_DrawLightPillar(pos);
}
