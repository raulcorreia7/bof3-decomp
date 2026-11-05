#include "area085_13.h"

MATCH void func_801F2CB4(void) {
    g_SpadWork->unk_09 -= 1;
    if (g_SpadWork->unk_09 != 0) {
        g_SpadWork->tint.bytes.unk_5D += 4;
        g_SpadWork->tint.bytes.unk_5E += 4;
        g_SpadWork->tint.bytes.unk_5F += 4;
    } else {
        g_SpadWork->unk_09 = 0xC;
        g_SpadWork->unk_01 = 3;
    }
    func_801F2ED8();
    func_801F2FCC();
}
