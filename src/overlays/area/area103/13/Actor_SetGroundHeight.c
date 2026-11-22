#include "area103_13.h"

/* func_801F57FC */
MATCH void Actor_SetGroundHeight(void) {
    s32 value = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);

    COORD_INT(TASK(Actor)->pos.z) = value;
}
