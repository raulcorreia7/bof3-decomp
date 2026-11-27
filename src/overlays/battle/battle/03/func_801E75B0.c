#include "battle_03.h"

MATCH void func_801E75B0(void) {
    u32 slot;

    if (g_BattleEffectBattler->unk_2C.value == 0) {
        slot = EMI_SLOT_REIU00;
        if (((u8*)g_BattleEffectBattler)[8] < 2u) {
            slot = EMI_SLOT_REID00;
        }
    } else {
        slot = EMI_SLOT_REIU01;
        if (((u8*)g_BattleEffectBattler)[8] < 2u) {
            slot = EMI_SLOT_REID01;
        }
    }
    EMI_ArchiveLoad(slot);
    SELF(PartyMember)->header.mode++;
}
