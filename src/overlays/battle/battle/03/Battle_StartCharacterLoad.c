#include "battle_03.h"

/* starts the EMI load of the party sprite archive of g_EmiLoadedCharacterIndex, front or back by the facing of
 * g_BattleEffectBattler, or one of the 513 to 520 variants while the party reloads, and advances the mode.
 */
/* func_801E7948 */
MATCH void Battle_StartCharacterLoad(void) {
    u32 slot;

    if (g_Battle.flags & BATTLE_STATE_RELOAD_PARTY) {
        if (func_801E7B34() & BYTE_MASK) {
            if (g_EmiLoadedCharacterIndex == 7) {
                slot = 517;
                if (g_BattleEffectBattler->facing < 2) {
                    slot = 513;
                }
                EMI_LoadArchive(slot);
            }
            if (g_EmiLoadedCharacterIndex == 0xD) {
                slot = 518;
                if (g_BattleEffectBattler->facing < 2) {
                    slot = 514;
                }
                EMI_LoadArchive(slot);
            }
            if (g_EmiLoadedCharacterIndex == 0xE) {
                slot = 519;
                if (g_BattleEffectBattler->facing < 2) {
                    slot = 515;
                }
                EMI_LoadArchive(slot);
            }
            if (g_EmiLoadedCharacterIndex == 0xF) {
                slot = 520;
                if (g_BattleEffectBattler->facing < 2) {
                    slot = 516;
                }
                EMI_LoadArchive(slot);
            }
        } else if (g_BattleEffectBattler->facing < 2) {
            EMI_LoadArchive(g_EmiLoadedCharacterIndex + EMI_SLOT_BPLD);
        } else {
            EMI_LoadArchive(g_EmiLoadedCharacterIndex + EMI_SLOT_BPLU);
        }
    } else if (g_BattleEffectBattler->facing < 2) {
        EMI_LoadArchive(D_800B4A64[g_EmiLoadedCharacterIndex]);
    } else {
        EMI_LoadArchive(D_800B4A68[g_EmiLoadedCharacterIndex]);
    }
    g_Task->header.mode++;
}
