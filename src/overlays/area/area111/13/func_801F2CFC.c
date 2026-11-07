#include "area111_13.h"

MATCH void func_801F2CFC(void) {
    u8     remaining;
    Actor* actor;

    func_801F2DA0(&g_Task->pos.x, (s16)g_Task->screen_x, (s16)g_Task->screen_y);
    actor     = g_Task;
    remaining = --actor->timer;
    actor->screen_x += 0x40;
    actor->screen_y += 0x40;
    if (remaining == 0) {
        g_Task->header.mode++;
    }
}
