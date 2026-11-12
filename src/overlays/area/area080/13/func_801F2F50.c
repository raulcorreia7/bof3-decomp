#include "area080_13.h"

MATCH void func_801F2F50(void) {
    u8 remaining;

    D_801F44A0->center[0] = D_80146954.x.fixed;
    D_801F44A0->center[1] = D_80146954.y.fixed;
    D_801F44A0->center[2] = D_80146954.z.fixed;
    Area_ProjectRing(D_801F44A0);
    func_801F31A0(D_801F44A0);
    func_801F33DC(D_801F44A0);
    func_801F3870();
    remaining     = g_Task->timer - 1;
    g_Task->timer = remaining;
    if (!(remaining & BYTE_MASK)) {
        g_Task->timer = AREA_RING_STEP_FRAMES;
        g_Task->header.mode += 1;
    }
}
