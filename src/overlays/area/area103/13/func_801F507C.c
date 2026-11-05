#include "area103_13.h"

MATCH void func_801F507C(void) {
    s32 temp_v0;
    s32 var_a0;

    temp_v0 = 0x1F - g_SpadWork->unk_09;
    var_a0  = temp_v0;
    if (temp_v0 < 0) {
        var_a0 = temp_v0 + 3;
    }
    func_801F5174(var_a0 >> 2, temp_v0 * 4);
    g_SpadWork->unk_09 += 1;
    if ((u8)g_SpadWork->unk_09 >= 0x19U) {
        g_SpadWork->unk_09 = 0;
        g_SpadWork->state_02 += 1;
    }
}
