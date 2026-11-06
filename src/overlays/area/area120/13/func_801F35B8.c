#include "area120_13.h"

MATCH void func_801F35B8(void) {
    u8* p;
    u16 i;

    g_Task->pos.x.fixed = TO_COORD(37);
    g_Task->pos.y.fixed = TO_COORD(116) + COORD_HALF;
    g_Task->pos.z.fixed = Area_SampleHeight(g_Task->pos.x.fixed, TO_COORD(116) + COORD_HALF) << 16;
    p                   = MEM_PTR(u8, AREA_WORK);
    for (i = 0; i < AREA_ROW_COUNT; i++) {
        *p = 0;
        p += AREA_ROW_STRIDE;
    }
}
