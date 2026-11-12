#include "battle_03.h"

MATCH void func_801E75B0(void) {
    u32 slot;

    if (g_BattleEffectBattler->unk_2C.half == 0) {
        slot = 574;
        if (((u8*)g_BattleEffectBattler)[8] < 2u) {
            slot = 572;
        }
    } else {
        slot = 575;
        if (((u8*)g_BattleEffectBattler)[8] < 2u) {
            slot = 573;
        }
    }
    EMI_LoadArchive(slot);
    g_Task->header.mode++;
}
