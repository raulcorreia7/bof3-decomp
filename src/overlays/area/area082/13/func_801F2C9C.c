#include "area082_13.h"

MATCH void func_801F2C9C(void) {
    u16 remaining;

    remaining          = g_SpadWork->unk_2C - 1;
    g_SpadWork->unk_2C = remaining;
    g_SpadWork->unk_64 += 4;
    g_SpadWork->unk_68 += 4;
    if (!(remaining & 0xFFFF)) {
        g_SpadWork->unk_2C = 0x10;
        g_SpadWork->unk_01 += 1;
    }
}
