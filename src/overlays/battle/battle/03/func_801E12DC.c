#include "battle_03.h"

/* when no active local damage row carries the 0x2000 flag, marks the local work word, records the work
 * pointer in the slot the route state selects and advances the work byte at 0x04.
 */
MATCH void func_801E12DC(void) {
    PartyBattler* work;
    PartyBattler* slot_work;
    u8            i;
    u32           slot;

    i = 0;
    while (i < g_BattlePartyCount) {
        if ((g_BattlePartyBattlers[i].flags_124.value & 0x2000u) != 0u) {
            return;
        }
        i++;
    }
    work = g_GameState;
    work->flags_124.value |= 0x2000u;
    if (work->stats.character_id == 4) {
        slot = Battle_AllocEffect(0, 0xB) & BYTE_MASK;
    } else {
        slot = Battle_AllocEffect(0, 0xC) & BYTE_MASK;
    }
    slot_work                          = g_SpadWork;
    g_BattleEffects[slot].target.party = slot_work;
    slot_work->unk_04++;
}
