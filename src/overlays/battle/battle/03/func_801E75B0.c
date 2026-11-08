#include "battle_03.h"

MATCH void func_801E75B0(void) {
    u32 slot;

    if (g_BattleEffectBattler->unk_2C.half == 0) {
        slot = 0x23E;
        if (((u8*)g_BattleEffectBattler)[8] < 2u) {
            slot = 0x23C;
        }
    } else {
        slot = 0x23F;
        if (((u8*)g_BattleEffectBattler)[8] < 2u) {
            slot = 0x23D;
        }
    }
    EMI_LoadArchive(slot);
    g_Task->header.mode++;
}
