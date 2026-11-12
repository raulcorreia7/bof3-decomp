#include "battle_03.h"

/* Slot tables selected by the battle work record's 0x08 byte; values are
 * stream-slot ids (u16). */

/* picks the next stream slot for the battle overlay: with the 0x8000 flag the hint selects a 0xF/0xE/0xD/7
 * variant by the work record's unk_08 (offset by 0x1DB/0x1EE when the query fails), without it the hint indexes the
 * D_800B4A64/D_800B4A68 slot table; starts the slot and advances the step byte.
 */
/* func_801E7948 */
MATCH void Battle_PickStreamSlot(void) {
    u32 slot;

    if (g_Battle.state & BATTLE_STATE_RELOAD_PARTY) {
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
