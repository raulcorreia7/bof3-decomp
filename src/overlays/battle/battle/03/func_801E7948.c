#include "battle_03.h"

/* Slot tables selected by the battle work record's 0x08 byte; values are
 * stream-slot ids (u16). */

/* picks the next stream slot for the battle overlay: with the 0x8000 flag the hint selects a 0xF/0xE/0xD/7
 * variant by the work record's unk_08 (offset by 0x1DB/0x1EE when the query fails), without it the hint indexes the
 * D_800B4A64/D_800B4A68 slot table; starts the slot and advances the step byte.
 */
MATCH void func_801E7948(void) {
    u32 slot;

    if (g_BattleState & BATTLE_STATE_RELOAD_PARTY) {
        if (func_801E7B34() & BYTE_MASK) {
            if (g_EmiLoadedCharacterIndex == 7) {
                slot = 0x205;
                if (D_801EB4E0->word_08.byte.unk_08 < 2) {
                    slot = 0x201;
                }
                EMI_LoaderStreamInitSlot(slot);
            }
            if (g_EmiLoadedCharacterIndex == 0xD) {
                slot = 0x206;
                if (D_801EB4E0->word_08.byte.unk_08 < 2) {
                    slot = 0x202;
                }
                EMI_LoaderStreamInitSlot(slot);
            }
            if (g_EmiLoadedCharacterIndex == 0xE) {
                slot = 0x207;
                if (D_801EB4E0->word_08.byte.unk_08 < 2) {
                    slot = 0x203;
                }
                EMI_LoaderStreamInitSlot(slot);
            }
            if (g_EmiLoadedCharacterIndex == 0xF) {
                slot = 0x208;
                if (D_801EB4E0->word_08.byte.unk_08 < 2) {
                    slot = 0x204;
                }
                EMI_LoaderStreamInitSlot(slot);
            }
        } else if (D_801EB4E0->word_08.byte.unk_08 < 2) {
            EMI_LoaderStreamInitSlot(g_EmiLoadedCharacterIndex + EMI_SLOT_BPLD);
        } else {
            EMI_LoaderStreamInitSlot(g_EmiLoadedCharacterIndex + EMI_SLOT_BPLU);
        }
    } else if (D_801EB4E0->word_08.byte.unk_08 < 2) {
        EMI_LoaderStreamInitSlot(D_800B4A64[g_EmiLoadedCharacterIndex]);
    } else {
        EMI_LoaderStreamInitSlot(D_800B4A68[g_EmiLoadedCharacterIndex]);
    }
    g_SpadWork->step_01++;
}
