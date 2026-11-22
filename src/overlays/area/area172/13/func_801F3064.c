#include "area172_13.h"

MATCH void func_801F3064(void) {
    u16 screen_x;
    u8  mode;

    screen_x         = g_Task->screen_x + 0x18;
    g_Task->screen_x = screen_x;
    func_801F36C0(&g_Task->pos.x, (s16)screen_x, 7);
    ACTOR_COUNT_DOWN(TASK(Actor), mode, timer);
    if (!(mode & BYTE_MASK)) {
        g_Task->timer = 64;
        g_Task->header.mode += 1;
    }
}
