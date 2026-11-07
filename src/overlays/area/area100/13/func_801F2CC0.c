#include "area100_13.h"

MATCH s32 func_801F2CC0(void) {
    s32 value;

    g_Task->pos.x.fixed = TO_COORD(10);
    g_Task->pos.y.fixed = TO_COORD(99);
    value               = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) << 16;
    g_Task->pos.z.fixed = value;
    g_Task->header.mode++;
}
