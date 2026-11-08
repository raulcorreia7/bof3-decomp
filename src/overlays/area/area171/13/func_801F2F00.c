#include "area171_13.h"

/* Draft matches; shared slide body needs typed origin and update. */
MATCH void func_801F2F00(void) {
    u16 screen_y;

    screen_y         = g_Task->screen_y + 0x10;
    g_Task->screen_y = screen_y;
    if ((s16)screen_y >= 0xC0) {
        g_Task->header.step += 1;
    }
    func_801F3070(0);
}
