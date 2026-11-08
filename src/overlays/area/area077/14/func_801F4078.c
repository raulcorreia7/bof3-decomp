#include "area077_14.h"
#include "area/spad.h"

MATCH void func_801F4078(void) {
    /* FAKE: retail reserves 16 bytes of unused stack. */
    FAKE_STACK_PADS(u8, 16);

    g_Task->pos.x.fixed = TO_COORD(116);
    g_Task->pos.y.fixed = TO_COORD(6);
    g_Task->pos.z.fixed = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) << 16;
    g_Task->vx          = 300;
    g_Task->header.mode++;
}
