#include "area175_13.h"

MATCH void func_801F35B4(void) {
    func_801F36DC((s16)g_Task->screen_x, (s16)g_Task->screen_y, g_Task->timer);
    g_Task->timer += 1;
    if (g_Task->timer >= 0x1FU) {
        g_Task->timer = 0x1E;
        g_Task->header.mode += 1;
    }
}
