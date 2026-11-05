#include "boss054_16.h"

MATCH void func_800C1C18(void) {
    u8* selector;
    u32 slot;
    u32 step;

    if (((PartyBattler*)g_Task)->word_08.byte.timer_0A == 0) {
        selector = (u8*)&g_BattleTargetSelector;
        if (Battle_SlotIsBlocked(*selector) & 0xFF) {
            ((PartyBattler*)g_Task)->mode = 9;
            return;
        }
        slot = *selector;
        if (slot < BATTLE_PARTY_SLOT_COUNT) {
            step = g_BattlePartyBattlers[slot].mode;
        } else {
            step = ENEMY_COMBATANT(slot).mode;
        }
        if (step != 6) {
            ((PartyBattler*)g_Task)->mode += 1;
        }
    }
}
