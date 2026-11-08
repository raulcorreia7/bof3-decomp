#include "boss054_16.h"

MATCH void func_800C1C18(void) {
    u8* selector;
    u32 slot;
    u32 step;

    if (((PartyMember*)g_Task)->timer == 0) {
        selector = (u8*)&g_Battle.target_selector;
        if (Battle_SlotIsBlocked(*selector) & 0xFF) {
            ((PartyMember*)g_Task)->header.mode = 9;
            return;
        }
        slot = *selector;
        if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
            step = g_Game.members[slot].header.mode;
        } else {
            step = ENEMY_COMBATANT(slot).header.mode;
        }
        if (step != 6) {
            ((PartyMember*)g_Task)->header.mode += 1;
        }
    }
}
