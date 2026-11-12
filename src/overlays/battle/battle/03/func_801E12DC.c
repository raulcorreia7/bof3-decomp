#include "battle_03.h"

/* when no active local damage row carries the 0x2000 flag, marks the local work word, records the work
 * pointer in the slot the route state selects and advances the work byte at 0x04.
 */
MATCH void func_801E12DC(void) {
    PartyMember* work;
    PartyMember* slot_work;
    u8           i;
    u32          slot;

    i = 0;
    while (i < g_Battle.party_count) {
        if ((g_Game.members[i].u.turn.damage_flags.value & COMBATANT_FLAG_FORM_EFFECT_PLAYING) != 0u) {
            return;
        }
        i++;
    }
    work = g_Game.current;
    work->u.turn.damage_flags.value |= COMBATANT_FLAG_FORM_EFFECT_PLAYING;
    if (work->chr.character_id == CHAR_ID_REI) {
        slot = Battle_AllocEffect(0, 11) & BYTE_MASK;
    } else {
        slot = Battle_AllocEffect(0, 12) & BYTE_MASK;
    }
    slot_work                          = g_Task;
    g_BattleEffects[slot].target.party = slot_work;
    slot_work->unk_04++;
}
