#include "game_00.h"

MATCH void Actor_Free(u8 record_index) {
    g_SpawnedActors[record_index].header.flags = 0;
    g_SpawnedActors[record_index].header.mode  = 0;
    g_SpawnedActors[record_index].header.step  = 0;
    g_SpawnedActors[record_index].unk_03       = 0;
    g_SpawnedActors[record_index].unk_04       = 0;
}
