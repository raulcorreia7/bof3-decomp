#include "battle_03.h"

/* finds the next local battler record with neither the 1 nor the 2 flag, marks it 0x2000, clears the first
 * three slot flags when its state is not 4, records it in the group slot and advances the selection counters.
 */
MATCH void func_801D6818(void) {
    u8  index;
    u32 offset;
    u8  slot;

    if (BATTLE_PARTY_CURSOR < g_BattlePartyCount) {
        do {
            if (Battle_SlotIsBlocked(BATTLE_PARTY_CURSOR) == 0u) {
                if (((g_BattlePartyBattlers[BATTLE_PARTY_CURSOR].flags_128.value & 1u) != 0u) ||
                    ((g_BattlePartyBattlers[BATTLE_PARTY_CURSOR].flags_128.value & 2u) != 0u)) {
                    g_BattlePartyBattlers[BATTLE_PARTY_CURSOR].flags_124.value |= 0x2000u;
                    if (g_BattlePartyBattlers[BATTLE_PARTY_CURSOR].stats.character_id == 4u) {
                        slot                               = (u8)Battle_AllocEffect(0u, 0xBu);
                        g_BattleEffects[slot].target.party = &g_BattlePartyBattlers[BATTLE_PARTY_CURSOR];
                    } else {
                        for (index = 0u; index < BATTLE_PARTY_SLOT_COUNT; index++) {
                            offset = (u32)index * BATTLE_PARTY_STRIDE;
                            *(u32*)((s_BattleBattlerTemplateTails + offset)) &= ~1u;
                        }
                        slot                               = (u8)Battle_AllocEffect(0u, 0xCu);
                        g_BattleEffects[slot].target.party = &g_BattlePartyBattlers[BATTLE_PARTY_CURSOR];
                    }
                    BATTLE_PARTY_CURSOR += 1u;
                    BATTLE_ENTRANCE_STEP += 1u;
                    return;
                }
            }
            BATTLE_PARTY_CURSOR += 1u;
        } while (BATTLE_PARTY_CURSOR < g_BattlePartyCount);
    }
    BATTLE_ENTRANCE_STEP += 1u;
}
