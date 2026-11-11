#include "area080_13.h"

MATCH void func_801F2E7C(void) {
    s16 radius;
    u8 timer;

    radius = D_801F44A0->radius + 0x30;
    D_801F44A0->radius = radius;
    if (radius > 0x180) {
        D_801F44A0->radius = 0x180;
    }
    Area_ProjectRing(D_801F44A0);
    func_801F31A0((s32)D_801F44A0);
    func_801F33DC(D_801F44A0);
    func_801F3870();
    timer = g_Task->timer - 1;
    g_Task->timer = timer;
    if ((timer & 0xFF) == 0) {
        g_Task->timer = 0x78;
        g_Task->header.mode++;
    }
}
