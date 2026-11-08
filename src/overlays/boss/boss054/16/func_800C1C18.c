#include "boss054_16.h"

MATCH void func_800C1C18(void) {
    u8* selector;
    u32 slot;
    u32 step;

    if (((PartyBattler*)g_Task)->timer == 0) {
        selector = (u8*)&g_BattleTargetSelector;
        if (Battle_SlotIsBlocked(*selector) & 0xFF) {
            ((PartyBattler*)g_Task)->header.mode = 9;
            return;
        }
        slot = *selector;
        if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
            step = g_BattlePartyBattlers[slot].header.mode;
        } else {
            step = ENEMY_COMBATANT(slot).header.mode;
        }
        if (step != 6) {
            ((PartyBattler*)g_Task)->header.mode += 1;
        }
    }
}
