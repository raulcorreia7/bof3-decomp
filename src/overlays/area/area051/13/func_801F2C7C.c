#include "area051_13.h"

MATCH void func_801F2C7C(void) {
    Actor* source;
    s32    y;

    source = g_CurrentActor;
    source -= 10;
    TASK(Actor)->pos.x.fixed      = source->pos.x.fixed;
    y                             = source->pos.y.fixed;
    TASK(Actor)->pos.y.fixed      = y;
    COORD_INT(TASK(Actor)->pos.z) = Area_HeightSample(TASK(Actor)->pos.x.fixed, y) - 0x40;
}
