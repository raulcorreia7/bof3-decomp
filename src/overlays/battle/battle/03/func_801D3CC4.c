#include "battle_03.h"

/* resets the action step of every queued battler and every overlay
 * slot that is still claimed, then arms the escape timer while nothing else
 * holds the phase.
 */
MATCH void func_801D3CC4(void) {
    u8 i;

    for (i = 0; (i & BYTE_MASK) < BATTLE_PARTY_CHARACTERS_COUNT; i += 1) {
        if (((g_BattlePartyBattlers[i].u.turn.damage_flags.value & COMBATANT_FLAG_DAMAGED) != 0) &&
            (g_BattlePartyBattlers[i].header.mode != 6)) {
            g_BattlePartyBattlers[i].header.mode = 6;
            g_BattlePartyBattlers[i].header.step = 0;
            g_BattlePartyBattlers[i].unk_03      = 0;
            g_BattlePartyBattlers[i].unk_04      = 0;
            Battle_SetSlotPending(i);
        }
    }
    for (i = 3; (i & BYTE_MASK) < COMBATANT_COUNT; i += 1) {
        if (((ENEMY_COMBATANT(i).turn.damage_flags.value & COMBATANT_FLAG_DAMAGED) != 0) &&
            (ENEMY_COMBATANT(i).header.mode != 6)) {
            ENEMY_COMBATANT(i).header.mode = 6;
            ENEMY_COMBATANT(i).header.step = 0;
            ENEMY_COMBATANT(i).unk_03      = 0;
            ENEMY_COMBATANT(i).unk_04      = 0;
            Battle_SetSlotPending(i);
        }
    }
    if (((func_800A99AC() & BYTE_MASK) == 0) && (D_801463C2 == 0) &&
        ((g_BattleState & BATTLE_STATE_EFFECT_PLAYING) != 0)) {
        g_BattleSubStep += 1;
    }
}
