#include "area103_13.h"

/* func_801F57FC */
MATCH void Actor_SetGroundHeight(void) {
    s32 value = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);

    COORD_INT(SELF(Actor)->pos.z) = value;
}
