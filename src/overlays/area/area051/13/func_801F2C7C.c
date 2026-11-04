#include "area051_13.h"

MATCH void func_801F2C7C(void) {
    Actor* source;
    s32    y;

    source = g_CurrentActor;
    source -= 10;
    g_SpadWork->x.fixed = source->x.fixed;
    y = source->y.fixed;
    g_SpadWork->y.fixed = y;
    g_SpadWork->z.part.integer = Area_SampleHeight(g_SpadWork->x.fixed, y) - 0x40;
}
