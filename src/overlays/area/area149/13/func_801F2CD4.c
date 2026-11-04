#include "area149_13.h"

MATCH void func_801F2CD4(void) {
    s8 value;
    u8 value2;

    value2             = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = value2;
    if (value2 & 0xFF) {
        g_AreaViewOffsetZ = (u16)g_AreaViewOffsetZ - 0x2A;
        value             = (s8)g_SpadWork->tint.bytes.unk_5D;
        if (value != 0) {
            g_SpadWork->tint.bytes.unk_5D = value - 1;
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
