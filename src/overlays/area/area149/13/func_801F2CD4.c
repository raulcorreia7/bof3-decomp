#include "area149_13.h"

MATCH void func_801F2CD4(void) {
    s8 temp_v0_2;
    u8 temp_v0;

    temp_v0            = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = temp_v0;
    if (temp_v0 & 0xFF) {
        g_AreaViewOffsetZ = (u16)g_AreaViewOffsetZ - 0x2A;
        temp_v0_2         = (s8)g_SpadWork->tint.bytes.unk_5D;
        if (temp_v0_2 != 0) {
            g_SpadWork->tint.bytes.unk_5D = temp_v0_2 - 1;
            g_SpadWork->tint.bytes.unk_5E -= 1;
            g_SpadWork->tint.bytes.unk_5F -= 1;
        }
    } else {
        g_AreaViewOffsetZ  = 0x400;
        g_SpadWork->unk_01 = 3;
    }
    g_AreaViewRefreshCount = 2;
    func_801F2DE0();
}
