#include "area075_13.h"

MATCH void func_801F2DD8(void) {
    u8 tint;

    tint                      = g_Task->tint.bytes.unk_5D - 2;
    g_Task->tint.bytes.unk_5D = tint;
    /* FAKE: the shift preserves the retail zero test. */
    if ((tint << 24) == 0) {
        Actor_Clear();
    }
    if (!(g_Task->tint.bytes.unk_5D & 0x1F)) {
        g_Task->unk_06 += 1;
    }
    func_801F2E64(g_Task->unk_06, 1);
}
