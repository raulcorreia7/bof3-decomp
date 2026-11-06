#include "area051_13.h"

MATCH void func_801F2C7C(void) {
    Actor* source;
    s32    y;

    source = g_CurrentActor;
    source -= 10;
    g_Task->pos.x.fixed      = source->pos.x.fixed;
    y                        = source->pos.y.fixed;
    g_Task->pos.y.fixed      = y;
    COORD_INT(g_Task->pos.z) = Area_SampleHeight(g_Task->pos.x.fixed, y) - 0x40;
}
