#include "area103_13.h"

MATCH void func_801F41EC(void) {
    s16 remaining;

    if (g_Task->timer == 15) {
        g_Task->timer = 0;
    }
    remaining = g_Task->unk_32;
    if (remaining > 0) {
        g_Task->unk_32 = remaining - 1;
    } else if (!((g_Task->timer / 5) & BYTE_MASK)) {
        g_Task->header.step += 1;
    }
    if (!((g_Task->timer % 5) & BYTE_MASK)) {
        func_801F4E70(((g_Task->timer / 5) & BYTE_MASK) + 7);
    }
    g_Task->timer += 1;
    func_801F49A0(1);
}
