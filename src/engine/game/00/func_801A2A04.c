#include "game_00.h"

MATCH u8 func_801A2A04(Actor* entity) {
    u8 saved;
    u8 i;

    saved = TASK(Actor)->direction & 0x7;
    i     = 0;

    while (i < 4u) {
        if ((func_801A1AE4(entity) & BYTE_MASK) == 0u) {
            break;
        }
        TASK(Actor)->direction = (TASK(Actor)->direction + 2) & 0x7;
        i++;
    }

    if (saved != TASK(Actor)->direction) {
        entity->interaction_flags |= ACTOR_INTERACTION_MOVING;
    }

    if (i < 4u) {
        return TASK(Actor)->direction & 0x7;
    }
    return 0xFF;
}
