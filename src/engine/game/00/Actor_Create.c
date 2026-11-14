#include "game_00.h"

/* K&R call keeps a0 undisturbed; the callee ignores its mode argument. */

MATCH void Actor_Create(u8* request) {
    u8 slot;

    slot = Actor_FindFreeSlot() & BYTE_MASK;
    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags      = 1;
        g_SpawnedActors[slot].type              = request[1];
        COORD_INT(g_SpawnedActors[slot].pos.x)  = request[3];
        COORD_FRAC(g_SpawnedActors[slot].pos.x) = (request[2] != 0) << 0xF;
        COORD_INT(g_SpawnedActors[slot].pos.y)  = request[5];
        COORD_FRAC(g_SpawnedActors[slot].pos.y) = (request[4] != 0) << 0xF;
        COORD_INT(g_SpawnedActors[slot].pos.z)  = Area_SampleHeight(g_SpawnedActors[slot].pos.x.fixed, g_SpawnedActors[slot].pos.y.fixed);
        g_SpawnedActors[slot].link              = request[6];
    }
}
