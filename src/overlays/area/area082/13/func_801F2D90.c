#include "area082_13.h"

MATCH void func_801F2D90(void) {
    u16 remaining;

    remaining      = g_Task->unk_2C - 1;
    g_Task->unk_2C = remaining;
    g_Task->unk_64 += 3;
    g_Task->unk_68 -= 3;
    if (!(remaining & HALF_MASK)) {
        g_Task->unk_2C = 0x10;
        g_Task->header.mode += 1;
    }
}
