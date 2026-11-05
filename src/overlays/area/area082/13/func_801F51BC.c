#include "area082_13.h"

MATCH void func_801F51BC(void) {
    D_8014933A = 0;
    func_801F5428(0x10001805);
    g_SpadWork->unk_30 -= 6;
    g_SpadWork->unk_32 = (g_SpadWork->unk_32 - (g_SpadWork->vz / 10000)) & 0xFFD;
    func_801F4430();
    g_SpadWork->unk_09 += 1;
    if ((u8)g_SpadWork->unk_09 >= 0x10U) {
        g_SpadWork->state_02 += 1;
    }
}
