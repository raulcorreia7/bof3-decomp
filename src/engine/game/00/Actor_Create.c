#include "game_00.h"

/* K&R call keeps a0 undisturbed; the callee ignores its mode argument. */

MATCH void Actor_Create(u8* request) {
    u8 slot;

    slot = Actor_FindFreeSlot() & BYTE_MASK;
    if (slot != GAME_NONE) {
        g_ActorSlots[slot].flags_00        = 1;
        g_ActorSlots[slot].type            = request[1];
        g_ActorSlots[slot].x.part.integer  = request[3];
        g_ActorSlots[slot].x.part.fraction = (request[2] != 0) << 0xF;
        g_ActorSlots[slot].y.part.integer  = request[5];
        g_ActorSlots[slot].y.part.fraction = (request[4] != 0) << 0xF;
        g_ActorSlots[slot].z.part.integer  = Area_SampleHeight(g_ActorSlots[slot].x.fixed, g_ActorSlots[slot].y.fixed);
        g_ActorSlots[slot].link_0B         = request[6];
    }
}
