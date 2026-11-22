#include "area099_13.h"

MATCH void func_801F2C40(void) {
    u8 slot;

    if (!(TASK(Actor)->direction & 0x1)) {
        TASK(Actor)->direction = (TASK(Actor)->direction - 1) & 0x7;
    }
    /* FAKE: retail reads SND_SEPlay as void(s32). */
    ((void (*)(s32))SND_SEPlay)(TASK(Actor)->unk_2C + 0x100);
    Script_Request(((TASK(Actor)->direction - 1) / 2) + 0x42);
    g_Game.current->u.field.flags |= 0x40;
    slot                          = Actor_FindFreeSpawned();
    TASK(Actor)->param.actor_slot = slot;
    if (TASK(Actor)->param.actor_slot != GAME_NONE) {
        g_SpawnedActors[TASK(Actor)->param.actor_slot].header.flags = 1;
        g_SpawnedActors[TASK(Actor)->param.actor_slot].type         = 0x1B;
    }
}
