#include "area171_13.h"

/* Draft matches; shared slide body needs typed origin and update. */
MATCH void func_801F2F00(void) {
    u16 temp_v0;

    temp_v0          = g_Task->screen_y + 0x10;
    g_Task->screen_y = temp_v0;
    if ((s16)temp_v0 >= 0xC0) {
        g_Task->header.step += 1;
    }
    func_801F3070(0);
}
