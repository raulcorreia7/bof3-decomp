#include "area119_13.h"

MATCH void func_801F3B98(void) {
    u8 index;

    if (g_AreaSceneMode == 0) {
        Actor_Clear();
        return;
    }
    SELF(Actor)->timer -= 1;
    if (SELF(Actor)->timer != 0) {
        return;
    }
    index = Actor_FindFreeSpawned();
    if (index != GAME_NONE) {
        g_SpawnedActors[index].header.flags = 1;
        g_SpawnedActors[index].type         = 0x18;
        g_SpawnedActors[index].header.mode  = 0x58;
        g_SpawnedActors[index].header.step  = 0;
        g_SpawnedActors[index].pos.x.fixed  = D_801F4614[SELF(Actor)->param.unk_0B].x << 12;
        g_SpawnedActors[index].pos.y.fixed  = D_801F4614[SELF(Actor)->param.unk_0B].y << 12;
        SELF(Actor)->timer                  = RANDOM_MASK(15) + 20;
        SELF(Actor)->param.unk_0B           = (SELF(Actor)->param.unk_0B + 1) & 0x7;
    }
}
