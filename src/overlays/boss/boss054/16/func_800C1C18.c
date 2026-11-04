#include "boss054_16.h"

MATCH void func_800C1C18(void) {
    u8* selector;
    u32 slot;
    u32 step;

    if (((PartyBattler*)g_SpadWork)->word_08.byte.unk_0A == 0) {
        selector = (u8*)&g_BattleTargetSelector;
        if (Battle_SlotIsBlocked(*selector) & 0xFF) {
            ((PartyBattler*)g_SpadWork)->step_01 = 9;
            return;
        }
        slot = *selector;
        if (slot < BATTLE_PARTY_SLOT_COUNT) {
            step = g_BattlePartyBattlers[slot].step_01;
        } else {
            step = ENEMY_COMBATANT(slot).step_01;
        }
        if (step != 6) {
            ((PartyBattler*)g_SpadWork)->step_01 += 1;
        }
    }
}
