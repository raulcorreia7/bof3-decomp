#include "area168_13.h"

MATCH void func_801F2C7C(void) {
    u8 i;

    for (i = 0; i < 6; i++) {
        func_801A4BC0(16, D_801F4B30[i], 0x89);
    }
    g_Task->header.mode = 1;
}
