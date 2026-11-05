#include "area098_13.h"

MATCH void func_801F3910(void) {
    u8 remaining;

    func_801F46EC(&g_SpadWork->unk_64, (s16)g_SpadWork->unk_2E, 6);
    remaining            = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = remaining;
    if (!(remaining & 0xFF)) {
        g_SpadWork->unk_09 = 0x20;
        g_SpadWork->unk_01 += 1;
    }
}
