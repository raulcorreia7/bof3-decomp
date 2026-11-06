#include "area077_14.h"
#include "work/area_spad.h"

MATCH void func_801F4078(void) {
    /* FAKE: retail reserves 16 bytes of unused stack. */
    STACK_PADS(u8, 16);

    g_Task->pos.x.fixed = 0x740000;
    g_Task->pos.y.fixed = 0x60000;
    g_Task->pos.z.fixed = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) << 16;
    g_Task->vx          = 300;
    g_Task->header.mode++;
}
