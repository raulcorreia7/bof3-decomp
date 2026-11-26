#include "area051_13.h"

MATCH void func_801F2C7C(void) {
    Actor* source;
    s32    y;

    source = g_CurrentActor;
    source -= 10;
    SELF(Actor)->pos.x.fixed      = source->pos.x.fixed;
    y                             = source->pos.y.fixed;
    SELF(Actor)->pos.y.fixed      = y;
    COORD_INT(SELF(Actor)->pos.z) = Area_HeightSample(SELF(Actor)->pos.x.fixed, y) - 0x40;
}
