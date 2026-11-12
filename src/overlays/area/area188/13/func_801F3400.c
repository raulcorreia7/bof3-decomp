#include "area188_13.h"

MATCH void func_801F3400(void) {
    u8 mode;

    func_801F38E0(&g_Task->unk_64, (s16)g_Task->screen_x, 6);
    mode          = g_Task->timer - 1;
    g_Task->timer = mode;
    if (!(mode & BYTE_MASK)) {
        g_Task->timer = 32;
        g_Task->header.mode += 1;
    }
}
