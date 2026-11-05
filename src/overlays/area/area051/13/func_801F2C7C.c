#include "area051_13.h"

MATCH void func_801F2C7C(void) {
    Actor* source;
    s32    y;

    source = g_CurrentActor;
    source -= 10;
    g_Task->x.fixed        = source->x.fixed;
    y                      = source->y.fixed;
    g_Task->y.fixed        = y;
    COORD_INT(g_Task->z) = Area_SampleHeight(g_Task->x.fixed, y) - 0x40;
}
