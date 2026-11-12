#include "battle_03.h"

/* finds the next local battler record with neither the 1 nor the 2 flag, marks it 0x2000, clears the first
 * three slot flags when its state is not 4, records it in the group slot and advances the selection counters.
 */
MATCH void func_801D6818(void) {
    u8 index;
    u8 slot;

    if (BATTLE_PARTY_CURSOR < g_Battle.party_count) {
        do {
            if (Battle_SlotIsBlocked(BATTLE_PARTY_CURSOR) == 0u) {
                if (((g_Game.members[BATTLE_PARTY_CURSOR].u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM_QUEUED) != 0u) ||
                    ((g_Game.members[BATTLE_PARTY_CURSOR].u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM) != 0u)) {
                    g_Game.members[BATTLE_PARTY_CURSOR].u.turn.damage_flags.value |= COMBATANT_FLAG_FORM_EFFECT_PLAYING;
                    if (g_Game.members[BATTLE_PARTY_CURSOR].chr.character_id == CHAR_ID_REI) {
                        slot                               = (u8)Battle_AllocEffect(0u, 11u);
                        g_BattleEffects[slot].target.party = &g_Game.members[BATTLE_PARTY_CURSOR];
                    } else {
                        for (index = 0u; index < BATTLE_PARTY_CHARACTERS_COUNT; index++) {
                            s_BattleBattlerTemplates[index].u.turn.action_flags.value &= ~COMBATANT_FLAG_DRAGON_FORM_QUEUED;
                        }
                        slot                               = (u8)Battle_AllocEffect(0u, 12u);
                        g_BattleEffects[slot].target.party = &g_Game.members[BATTLE_PARTY_CURSOR];
                    }
                    BATTLE_PARTY_CURSOR += 1u;
                    BATTLE_ENTRANCE_STEP += 1u;
                    return;
                }
            }
            BATTLE_PARTY_CURSOR += 1u;
        } while (BATTLE_PARTY_CURSOR < g_Battle.party_count);
    }
    BATTLE_ENTRANCE_STEP += 1u;
}
