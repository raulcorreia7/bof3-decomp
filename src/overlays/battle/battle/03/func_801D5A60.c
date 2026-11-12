#include "battle_03.h"

MATCH u8 func_801D5A60(void) {
    u8 index;
    u8 count;
    u8 last_index;

    count      = 0u;
    last_index = 0u;
    for (index = 3u; index < 11u; index++) {
        if ((func_801D64C4(index) == 0u) && ((ENEMY_COMBATANT(index).status & STATUS_CONFUSED) != 0u)) {
            if (func_801DDCB4(index) != 0u) {
                last_index                          = index;
                ENEMY_COMBATANT(index).turn.counter = 0u;
                ENEMY_COMBATANT(index).status &= ~STATUS_CONFUSED;
                count += 1u;
            } else {
                ENEMY_COMBATANT(index).turn.counter += 1u;
            }
        }
    }

    if (count != 0u) {
        u32 event_id;
        u8* text;

        func_801D9484();
        event_id = 0x2Au;
        if (count == 1u) {
            Battle_SetTextEnemyName(last_index);
            event_id = 0x28u;
        }
        text = Message_GetText(event_id);
        func_801DE560(2u, 0u, 0u, 45u, text);
        return true;
    }

    return false;
}
