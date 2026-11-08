#include "area168_13.h"

MATCH void func_801F2C7C(void) {
    u8 i = 0;
    u8 row;

    do {
        row = D_801F4B30[i];
        i++;
        func_801A4BC0(16, row, 0x89);
    } while (i < 6);
    g_Task->header.mode = 1;
}
