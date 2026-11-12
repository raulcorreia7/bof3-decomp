#include "area172_13.h"

MATCH void func_801F3064(void) {
    u16 screen_x;
    u8  mode;

    screen_x         = g_Task->screen_x + 0x18;
    g_Task->screen_x = screen_x;
    func_801F36C0(&g_Task->pos.x, (s16)screen_x, 7);
    mode          = g_Task->timer - 1;
    g_Task->timer = mode;
    if (!(mode & BYTE_MASK)) {
        g_Task->timer = 64;
        g_Task->header.mode += 1;
    }
}
