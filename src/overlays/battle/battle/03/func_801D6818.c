#include "battle_03.h"

/* finds the next local battler record with neither the 1 nor the 2 flag, marks it 0x2000, clears the first
 * three slot flags when its state is not 4, records it in the group slot and advances the selection counters.
 */
MATCH void func_801D6818(void) {
    u8  index;
    u32 offset;
    u8  slot;

    if (((u8*)&D_80140000)[0x62E5] < g_BattlePartyCount) {
        do {
            if (Battle_SlotIsBlocked(((u8*)&D_80140000)[0x62E5]) == 0u) {
                if (((g_BattlePartyBattlers[((u8*)&D_80140000)[0x62E5]].flags_128.value & 1u) != 0u) ||
                    ((g_BattlePartyBattlers[((u8*)&D_80140000)[0x62E5]].flags_128.value & 2u) != 0u)) {
                    g_BattlePartyBattlers[((u8*)&D_80140000)[0x62E5]].flags_124.value |= 0x2000u;
                    if (g_BattlePartyBattlers[((u8*)&D_80140000)[0x62E5]].stats.character_id == 4u) {
                        slot                                = (u8)Battle_AllocEffect(0u, 0xBu);
                        g_BattleEffects[slot].work_74.party = &g_BattlePartyBattlers[((u8*)&D_80140000)[0x62E5]];
                    } else {
                        for (index = 0u; index < BATTLE_PARTY_SLOT_COUNT; index++) {
                            offset = (u32)index * BATTLE_PARTY_STRIDE;
                            *(u32*)((s_BattleBattlerTemplateTails + offset)) &= ~1u;
                        }
                        slot                                = (u8)Battle_AllocEffect(0u, 0xCu);
                        g_BattleEffects[slot].work_74.party = &g_BattlePartyBattlers[((u8*)&D_80140000)[0x62E5]];
                    }
                    ((u8*)&D_80140000)[0x62E5] += 1u;
                    ((u8*)&D_80140000)[0x62E2] += 1u;
                    return;
                }
            }
            ((u8*)&D_80140000)[0x62E5] += 1u;
        } while (((u8*)&D_80140000)[0x62E5] < g_BattlePartyCount);
    }
    ((u8*)&D_80140000)[0x62E2] += 1u;
}
