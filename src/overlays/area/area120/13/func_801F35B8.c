#include "area120_13.h"

MATCH void func_801F35B8(void) {
    u8* p;
    u16 i;

    g_SpadWork->x.fixed = 0x250000;
    g_SpadWork->y.fixed = 0x748000;
    g_SpadWork->z.fixed = Area_SampleHeight(g_SpadWork->x.fixed, 0x748000) << 16;
    p                   = MEM_PTR(u8, AREA_WORK);
    for (i = 0; i < AREA_ROW_COUNT; i++) {
        *p = 0;
        p += AREA_ROW_STRIDE;
    }
}
