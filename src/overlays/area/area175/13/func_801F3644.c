#include "area175_13.h"

MATCH void func_801F3644(void) {
    u8 mode;

    func_801F36DC((s16)g_Task->screen_x, (s16)g_Task->screen_y, g_Task->timer);
    mode          = g_Task->timer - 1;
    g_Task->timer = mode;
    if (!(mode & BYTE_MASK)) {
        g_Task->header.mode += 1;
    }
}
