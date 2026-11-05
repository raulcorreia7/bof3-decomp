#include "area088_13.h"

MATCH void func_801F2D80(void) {
    u8 temp_v0;

    func_801F2F28((u8*)0x800E4800);
    func_801F3258((u8*)0x800E4800);
    temp_v0            = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->unk_09 = 0x10;
        g_SpadWork->unk_01 += 1;
    }
}
