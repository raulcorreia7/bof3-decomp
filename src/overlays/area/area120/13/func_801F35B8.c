#include "area120_13.h"

MATCH void func_801F35B8(void) {
    u8* p;
    u16 i;

    TASK(Actor)->pos.x.fixed = TO_COORD(37);
    TASK(Actor)->pos.y.fixed = TO_COORD(116) + COORD_HALF;
    TASK(Actor)->pos.z.fixed = Area_HeightSample(TASK(Actor)->pos.x.fixed, TO_COORD(116) + COORD_HALF) << 16;
    p                        = MEM_PTR(u8, AREA_WORK);
    for (i = 0; i < AREA_EFFECT_COUNT; i++) {
        *p = 0;
        p += AREA_EFFECT_STRIDE;
    }
}
