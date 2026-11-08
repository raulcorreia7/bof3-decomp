#include "area103_13.h"

/* func_801F57FC */
MATCH void Actor_SetGroundHeight(void) {
    s32 value = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);

    COORD_INT(g_Task->pos.z) = value;
}
