#include "engine/game/00/game_00.h"

/* func_801A2A04 */
/* Turns by two facings up to four times to the first one with a free cell ahead; returns it or 0xFF. */
MATCH u8 Actor_FindFreeFacing(Actor* entity) {
    u8 saved;
    u8 i;

    saved = TASK(Actor)->direction & 0x7;
    i     = 0;

    while (i < 4u) {
        if ((Actor_IsAheadBlocked(entity) & BYTE_MASK) == 0u) {
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
