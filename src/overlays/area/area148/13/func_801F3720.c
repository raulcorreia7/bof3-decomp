#include "area148_13.h"

MATCH void func_801F3720(void) {
    g_Task->screen_y = (g_Task->screen_y + 8);
    if ((s16)g_Task->screen_y >= 0x80) {
        g_Task->header.step++;
    }
    func_801F37B8(0, -1);
    func_801F37B8(1, 1);
}
