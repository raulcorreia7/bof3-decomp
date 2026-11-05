#include "area082_13.h"

MATCH void func_801F2C9C(void) {
    u16 temp_v0;

    temp_v0            = g_SpadWork->unk_2C - 1;
    g_SpadWork->unk_2C = temp_v0;
    g_SpadWork->unk_64 += 4;
    g_SpadWork->unk_68 += 4;
    if (!(temp_v0 & 0xFFFF)) {
        g_SpadWork->unk_2C = 0x10;
        g_SpadWork->unk_01 += 1;
    }
}
