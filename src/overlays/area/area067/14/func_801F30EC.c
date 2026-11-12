#include "area067_14.h"

MATCH void func_801F30EC(void) {
    /* The mode's quad and its height live in the task's velocity words. */
    u16* quad = (u16*)g_Task;
    u16* pos  = &quad[6];
    u8   timer;

    func_801F3AD8(pos);
    quad[9] += 2;
    quad[7] -= quad[9];
    func_801F3AD8(pos);
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        g_Task->header.mode += 1;
    }
}
