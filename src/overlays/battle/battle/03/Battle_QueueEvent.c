#include "battle_03.h"

/* func_801DE560 */
MATCH void Battle_QueueEvent(u8 event_type, u8 event_value, u8 group, u8 timer, u8* payload) {
    u8 index;
    u8 value;

    index = 2u;
    while (index < 8u) {
        value = g_BattleEventSlots[index].active;
        if (value == 0u) {
            g_BattleEventSlots[index].active     = value | 0x1u;
            g_BattleEventSlots[index].event_type = event_type;
            g_BattleEventSlots[index].value      = event_value;
            g_BattleEventSlots[index].group      = group;
            g_BattleEventSlots[index].timer      = timer;
            g_BattleEventSlots[index].payload    = payload;
            g_BattleEventSlots[index].text_style = 0u;
            return;
        }
        index += 1u;
    }
}
