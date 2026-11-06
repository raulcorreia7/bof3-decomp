#include "area068_13.h"

MATCH void func_801F3074(void) {
    if (D_801F4E08 == 0) {
        g_Task->header.mode = 0x16;
    } else {
        D_801F4E0C          = 0;
        g_Task->header.mode = 0xB;
    }
}
