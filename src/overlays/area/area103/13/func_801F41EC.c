#include "area103_13.h"

MATCH void func_801F41EC(void) {
    s16 temp_v0;

    if (g_SpadWork->unk_09 == 0xF) {
        g_SpadWork->unk_09 = 0;
    }
    temp_v0 = (s16)g_SpadWork->unk_32;
    if (temp_v0 > 0) {
        g_SpadWork->unk_32 = temp_v0 - 1;
    } else if (!((g_SpadWork->unk_09 / 5) & 0xFF)) {
        g_SpadWork->state_02 += 1;
    }
    if (!((g_SpadWork->unk_09 % 5) & 0xFF)) {
        func_801F4E70(((g_SpadWork->unk_09 / 5) & 0xFF) + 7);
    }
    g_SpadWork->unk_09 += 1;
    func_801F49A0(1);
}
