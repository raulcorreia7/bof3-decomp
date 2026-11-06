#include "game_00.h"

/* K&R call keeps a0 undisturbed; the callee ignores its mode argument. */

MATCH void Actor_Create(u8* request) {
    u8 slot;

    slot = Actor_FindFreeSlot() & BYTE_MASK;
    if (slot != GAME_NONE) {
        g_ActorSlots[slot].header.flags  = 1;
        g_ActorSlots[slot].type          = request[1];
        COORD_INT(g_ActorSlots[slot].x)  = request[3];
        COORD_FRAC(g_ActorSlots[slot].x) = (request[2] != 0) << 0xF;
        COORD_INT(g_ActorSlots[slot].y)  = request[5];
        COORD_FRAC(g_ActorSlots[slot].y) = (request[4] != 0) << 0xF;
        COORD_INT(g_ActorSlots[slot].z)  = Area_SampleHeight(g_ActorSlots[slot].x.fixed, g_ActorSlots[slot].y.fixed);
        g_ActorSlots[slot].link          = request[6];
    }
}
