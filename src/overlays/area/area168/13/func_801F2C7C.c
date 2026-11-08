#include "area168_13.h"

MATCH void func_801F2C7C(void) {
    s32 i;

    i = 0;
    do {
        func_801A4BC0(0x10, D_801F4B30[i & 0xFF], 0x89);
        i++;
    } while ((u32)(i & 0xFF) < 6);
    g_Task->header.mode = 1;
}
