#include "battle_03.h"

MATCH void func_801E64B4(void) {
    BattleEffect* slot;
    s32           value;

    g_AreaCameraOffsetZ -= (u16)D_801EC2E0->unk_0C;
    GFX_AddDrawMode(GetTPage(0, 0, 960, 0));
    if (BATTLER_IS_PLAYER(g_BattleActiveBattler)) {
        value = D_801EC2E0->unk_10;
        func_801D9DBC(0, 0, 0xB, ((value << 10) + (value << 5) + value) & HALF_MASK, 1);
    } else {
        func_801D9DBC(0, 0, 0xB, (D_801EC2E0->unk_10 << 10) & 0xFC00, 1);
    }
    slot                     = D_801EC2E0;
    g_AreaCameraRefreshCount = 2;
    slot->unk_10 += 8;
    if (slot->unk_09 != 0) {
        slot->unk_09 -= 1;
        return;
    }
    slot->mode += 1;
    D_801EC2E0->unk_09 = 2;
}
