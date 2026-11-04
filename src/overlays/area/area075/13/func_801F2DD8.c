#include "area075_13.h"

MATCH void func_801F2DD8(void) {
    u8 tint;

    tint                          = g_SpadWork->tint.bytes.unk_5D - 2;
    g_SpadWork->tint.bytes.unk_5D = tint;
    /* FAKE: the shift preserves the retail zero test. */
    if (((u32)tint << 24) == 0) {
        func_80196070();
    }
    if (!(g_SpadWork->tint.bytes.unk_5D & 0x1F)) {
        g_SpadWork->unk_06 += 1;
    }
    func_801F2E64(g_SpadWork->unk_06, 1);
}
