#include "area098_13.h"

MATCH void func_801F3910(void) {
    u8 remaining;

    func_801F46EC(&g_Task->unk_64, (s16)g_Task->screen_x, 6);
    remaining     = g_Task->timer - 1;
    g_Task->timer = remaining;
    if (!(remaining & BYTE_MASK)) {
        g_Task->timer = 32;
        g_Task->header.mode += 1;
    }
}
