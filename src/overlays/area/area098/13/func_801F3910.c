#include "area098_13.h"

MATCH void func_801F3910(void) {
    u8 temp_v0;

    func_801F46EC(&g_SpadWork->unk_64, (s16)g_SpadWork->unk_2E, 6);
    temp_v0            = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->unk_09 = 0x20;
        g_SpadWork->unk_01 += 1;
    }
}
