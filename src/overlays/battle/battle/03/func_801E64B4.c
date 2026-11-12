#include "battle_03.h"

MATCH void func_801E64B4(void) {
    BattleEffect* slot;
    s32           value;

    g_AreaCameraOffsetZ -= D_801EC2E0->unk_0C;
    GFX_AddDrawMode(GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));
    if (BATTLER_IS_PLAYER(g_Battle.active_battler)) {
        value = D_801EC2E0->unk_10;
        func_801D9DBC(0, 0, 11, ((value << 10) + (value << 5) + value) & HALF_MASK, 1);
    } else {
        func_801D9DBC(0, 0, 11, (D_801EC2E0->unk_10 << 10) & 0xFC00, 1);
    }
    slot                     = D_801EC2E0;
    g_AreaCameraRefreshCount = 2;
    slot->unk_10 += 8;
    if (slot->arg.unk_09 != 0) {
        slot->arg.unk_09 -= 1;
        return;
    }
    slot->header.mode += 1;
    D_801EC2E0->arg.unk_09 = 2;
}
