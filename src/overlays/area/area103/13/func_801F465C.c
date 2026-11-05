#include "area103_13.h"

MATCH void func_801F465C(void) {
    s16 count;

    if (g_SpadWork->unk_09 == 0xF) {
        g_SpadWork->unk_09 = 0;
    }
    count = (s16)g_SpadWork->unk_32;
    if (count > 0) {
        g_SpadWork->unk_32 = count - 1;
    } else if (!((g_SpadWork->unk_09 / 5) & 0xFF)) {
        g_SpadWork->state_02 += 1;
    }
    if (!((g_SpadWork->unk_09 % 5) & 0xFF)) {
        func_801F4E70(((g_SpadWork->unk_09 / 5) & 0xFF) + 7);
    }
    g_SpadWork->unk_09 += 1;
    Area_SetCellPalette(0x42, (s16)(((s16)g_SpadWork->unk_32 / 6) + 0x18));
}
