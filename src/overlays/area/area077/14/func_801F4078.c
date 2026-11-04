#include "area077_14.h"
#include "work/area_spad.h"

MATCH void func_801F4078(void) {
    /* FAKE: retail reserves 16 bytes of unused stack. */
    STACK_PADS(u8, 16);

    g_SpadWork->x.fixed = 0x740000;
    g_SpadWork->y.fixed = 0x60000;
    g_SpadWork->z.fixed = Area_SampleHeight(g_SpadWork->x.fixed, g_SpadWork->y.fixed) << 16;
    g_SpadWork->unk_0C = 300;
    g_SpadWork->unk_01++;
}
