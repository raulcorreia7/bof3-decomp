#include "game_00.h"

MATCH void Actor_ClearAll(void) {
    u8 record_index;

    record_index = 0u;
    while (record_index < ACTOR_SLOT_COUNT) {
        Actor_Free(record_index);
        record_index += 1u;
    }
}
