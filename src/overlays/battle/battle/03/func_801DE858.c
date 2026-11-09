#include "battle_03.h"

/* event-queue slot array: stride 12 (0xC); byte 0 = active flag, byte 1 = event
 * type. */

MATCH u8 func_801DE858(s8 event_kind) {
    u8  index;
    u32 offset;

    index = 0u;
    while (index < 8u) {
        offset = index * 12u;
        if ((((volatile u8*)g_BattleEventSlots)[offset] != 0u) &&
            (((volatile u8*)g_BattleEventSlots + 1)[offset] == (u8)event_kind)) {
            return false;
        }
        index += 1u;
    }
    return true;
}
