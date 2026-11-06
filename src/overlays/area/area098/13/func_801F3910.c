#include "area098_13.h"

MATCH void func_801F3910(void) {
    u8 remaining;

    func_801F46EC(&g_Task->unk_64, (s16)g_Task->unk_2E, 6);
    remaining      = g_Task->unk_09 - 1;
    g_Task->unk_09 = remaining;
    if (!(remaining & 0xFF)) {
        g_Task->unk_09 = 0x20;
        g_Task->header.mode += 1;
    }
}
