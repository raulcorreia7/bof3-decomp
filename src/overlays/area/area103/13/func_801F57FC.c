#include "area103_13.h"

MATCH void func_801F57FC(void) {
    s32 value = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);

    COORD_INT(g_Task->pos.z) = value;
}
