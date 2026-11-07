#include "area157_13.h"

MATCH void func_801F3718(void) {
    g_Task->screen_y += 0x20;
    if ((s16)g_Task->screen_y >= 0x100) {
        g_Task->header.step++;
    }
}
