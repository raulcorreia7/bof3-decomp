#include "area103_13.h"

MATCH void func_801F41EC(void) {
    s16 remaining;

    if (g_Task->unk_09 == 0xF) {
        g_Task->unk_09 = 0;
    }
    remaining = g_Task->unk_32;
    if (remaining > 0) {
        g_Task->unk_32 = remaining - 1;
    } else if (!((g_Task->unk_09 / 5) & 0xFF)) {
        g_Task->header.step += 1;
    }
    if (!((g_Task->unk_09 % 5) & 0xFF)) {
        func_801F4E70(((g_Task->unk_09 / 5) & 0xFF) + 7);
    }
    g_Task->unk_09 += 1;
    func_801F49A0(1);
}
