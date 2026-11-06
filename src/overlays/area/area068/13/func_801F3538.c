#include "area068_13.h"

MATCH void func_801F3538(void) {
    if (g_InputPressed == PADRdown) {
        D_801F4E04 += 1;
        g_Task->header.mode = 0x10;
    }
}
