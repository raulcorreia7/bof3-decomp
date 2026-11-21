#include "engine/game/00/game_00.h"

MATCH u8 Actor_FindFreeSpawned(void) {
    u8 i;

    for (i = 0; i < ACTOR_SLOT_COUNT; i++) {
        if (g_SpawnedActors[i].header.flags == 0) {
            return i;
        }
    }
    return 0xFF;
}
