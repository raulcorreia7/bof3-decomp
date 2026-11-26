#include "battle_03.h"

/* starts the EMI load of the party sprite archive of g_EmiLoadedCharacterIndex, front or back by the facing of
 * g_BattleEffectBattler, or one of the BRT variants while the party reloads, and advances the mode.
 */
/* func_801E7948 */
MATCH void Battle_StartCharacterLoad(void) {
    u32 slot;

    if (g_Battle.flags & BATTLE_STATE_RELOAD_PARTY) {
        if (func_801E7B34() & BYTE_MASK) {
            if (g_EmiLoadedCharacterIndex == 7) {
                slot = EMI_SLOT_BRTU247;
                if (g_BattleEffectBattler->facing < 2) {
                    slot = EMI_SLOT_BRTD247;
                }
                EMI_ArchiveLoad(slot);
            }
            if (g_EmiLoadedCharacterIndex == 0xD) {
                slot = EMI_SLOT_BRTU457;
                if (g_BattleEffectBattler->facing < 2) {
                    slot = EMI_SLOT_BRTD457;
                }
                EMI_ArchiveLoad(slot);
            }
            if (g_EmiLoadedCharacterIndex == 0xE) {
                slot = EMI_SLOT_BRTU467;
                if (g_BattleEffectBattler->facing < 2) {
                    slot = EMI_SLOT_BRTD467;
                }
                EMI_ArchiveLoad(slot);
            }
            if (g_EmiLoadedCharacterIndex == 0xF) {
                slot = EMI_SLOT_BRTU478;
                if (g_BattleEffectBattler->facing < 2) {
                    slot = EMI_SLOT_BRTD478;
                }
                EMI_ArchiveLoad(slot);
            }
        } else if (g_BattleEffectBattler->facing < 2) {
            EMI_ArchiveLoad(g_EmiLoadedCharacterIndex + EMI_SLOT_BPLD);
        } else {
            EMI_ArchiveLoad(g_EmiLoadedCharacterIndex + EMI_SLOT_BPLU);
        }
    } else if (g_BattleEffectBattler->facing < 2) {
        EMI_ArchiveLoad(D_800B4A64[g_EmiLoadedCharacterIndex]);
    } else {
        EMI_ArchiveLoad(D_800B4A68[g_EmiLoadedCharacterIndex]);
    }
    SELF(PartyMember)->header.mode++;
}
