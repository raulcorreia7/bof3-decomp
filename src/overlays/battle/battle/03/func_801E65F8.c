#include "battle_03.h"

MATCH void func_801E65F8(void) {
    BattleEffect* slot;
    s32           value;
    u8            count;

    g_AreaCameraOffsetZ += D_801EC2E0->unk_0C;
    GFX_AddDrawMode(GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));
    if (BATTLER_IS_PLAYER(g_Battle.active_battler)) {
        /* Replicates the slot's +0x10 cell into all three 5-bit color channels. */
        value = D_801EC2E0->unk_10;
        func_801D9DBC(0, 0, 11, ((value << 0xA) + (value << 5) + value) & HALF_MASK, 1);
    } else {
        /* Only the red channel of the scaled color is kept. */
        func_801D9DBC(0, 0, 11, (D_801EC2E0->unk_10 << 0xA) & 0xFC00, 1);
    }
    slot                     = D_801EC2E0;
    g_AreaCameraRefreshCount = 2;
    slot->unk_10 -= 8;
    count = slot->arg.unk_09;
    if (count != 0) {
        slot->arg.unk_09 = count - 1;
        return;
    }
    Effect_Reset();
}
