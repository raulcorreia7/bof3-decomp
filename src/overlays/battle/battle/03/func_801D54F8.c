#include "battle_03.h"

MATCH u8 func_801D54F8(void) {
    u8 index;
    u8 count;
    u8 last_index;

    count      = 0u;
    last_index = 0u;
    for (index = 0u; index < BATTLE_PARTY_CHARACTERS_COUNT; index++) {
        if ((Battle_GetActionLock(index) == 0u) && (HAS_STATUS(g_Game.members[index], 0x800u)) && (g_Game.members[index].counter_137 == 5u)) {
            last_index = index;
            count += 1u;
            g_Game.members[index].counter_137   = 0u;
            g_Game.members[index].chr.hp        = g_Game.members[index].chr.stats.max_hp;
            g_Game.members[index].chr.ap        = g_Game.members[index].chr.stats.max_ap;
            g_Game.members[index].chr.willpower = g_Game.members[index].chr.stats.willpower;
            func_800A36F0(index, 0x8FFu);
        }
    }

    if (count != 0u) {
        u32 event_id;
        u8* text;

        Battle_OpenPanel();
        event_id = 0x2Cu;
        if (count == 1u) {
            Battle_SetTextPartyName(last_index);
            event_id = 0x2Bu;
        }
        text = Message_GetText(event_id);
        Battle_QueueEvent(2u, 0u, 0u, 45u, text);
        return true;
    }

    return false;
}
