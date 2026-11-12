#include "area130_13.h"

MATCH void func_801F3284(void) {
    u16* cell;
    u8   timer;

    cell = &D_801469EA;
    *cell += 0xF00;
    g_Task->vx += 15;
    g_Task->vy += 10;
    func_801F3400(g_Task->screen_x, g_Task->screen_y, g_Task->vx, g_Task->vy);
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        g_Task->timer = 60;
        g_Task->header.mode++;
    }
}
