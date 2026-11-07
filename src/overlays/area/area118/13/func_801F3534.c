#include "area118_13.h"

MATCH void func_801F3534(void) {
    g_Task->screen_y -= 0x20;
    if ((s16)g_Task->screen_y < -0xFF) {
        g_Task->header.step++;
    }
    func_801F381C(0);
}
