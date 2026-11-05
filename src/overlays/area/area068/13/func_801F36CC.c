#include "area068_13.h"

MATCH void func_801F36CC(void) {
    u8 timer;

    timer      = D_801F4E00 - 1;
    D_801F4E00 = timer;
    if (timer == 0) {
        D_801F4E00   = 0;
        g_Task->mode = 0x14;
    } else if (g_InputPressed == PADRdown) {
        D_801F4E0C = 0;
        D_801F4E04++;
        g_Task->mode = 0x10;
    } else {
        g_Task->mode = 0x11;
    }
}
