#include "battle_03.h"

MATCH u8 func_801D590C(void) {
    u8 index;
    u8 count;
    u8 last_index;

    count      = 0u;
    last_index = 0u;
    for (index = 0u; index < BATTLE_PARTY_CHARACTERS_COUNT; index++) {
        if ((Battle_GetActionLock(index) == 0u) && (HAS_STATUS(g_Game.members[index], STATUS_CONFUSED))) {
            if (func_801DDCB4(index) != 0u) {
                last_index                           = index;
                g_Game.members[index].u.turn.counter = 0u;
                g_Game.members[index].chr.status &= ~STATUS_CONFUSED;
                count += 1u;
            } else {
                g_Game.members[index].u.turn.counter += 1u;
            }
        }
    }

    if (count != 0u) {
        u32 event_id;
        u8* text;

        Battle_OpenPanel();
        event_id = 0x29u;
        if (count == 1u) {
            Battle_SetTextPartyName(last_index);
            event_id = 0x28u;
        }
        text = Message_GetText(event_id);
        Battle_QueueEvent(2u, 0u, 0u, 45u, text);
        return true;
    }

    return false;
}
