#include "game_00.h"

MATCH u8 func_801A2A04(Actor* entity) {
    u8 saved;
    u8 i;

    saved = g_Task->direction_08 & 0x7;
    i     = 0;

    while (i < 4u) {
        if ((func_801A1AE4(entity) & BYTE_MASK) == 0u) {
            break;
        }
        g_Task->direction_08 = (g_Task->direction_08 + 2) & 0x7;
        i++;
    }

    if (saved != g_Task->direction_08) {
        entity->interaction_flags |= ACTOR_FLAG_MOVING;
    }

    if (i < 4u) {
        return g_Task->direction_08 & 0x7;
    }
    return 0xFF;
}
