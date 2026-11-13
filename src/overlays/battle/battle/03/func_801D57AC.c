#include "battle_03.h"

MATCH u8 func_801D57AC(void) {
    u8 index;
    u8 count;
    u8 last_index;

    count      = 0u;
    last_index = 0u;
    for (index = 3u; index < 11u; index++) {
        if ((Battle_GetActionLock(index) == 0u) && ((ENEMY_COMBATANT(index).status & STATUS_SLEEPING) != 0u)) {
            if (func_801DDCB4(index) != 0u) {
                last_index                          = index;
                ENEMY_COMBATANT(index).turn.counter = 0u;
                ENEMY_COMBATANT(index).status &= ~STATUS_SLEEPING;
                count += 1u;
            } else {
                ENEMY_COMBATANT(index).turn.counter += 1u;
            }
        }
    }

    if (count != 0u) {
        u32 event_id;
        u8* text;

        Battle_OpenPanel();
        event_id = 0x27u;
        if (count == 1u) {
            Battle_SetTextEnemyName(last_index);
            event_id = 0x25u;
        }
        text = Message_GetText(event_id);
        Battle_QueueEvent(2u, 0u, 0u, 45u, text);
        return true;
    }

    return false;
}
