#include "area100_13.h"

MATCH void func_801F369C(void) {
    SpawnedActor* actor;
    s32        slot;

    g_AreaSceneMode = 1;
    Area_SetCellPalette(74, 47);
    slot = Actor_FindFreeSlot() & BYTE_MASK;
    if (slot != GAME_NONE) {
        actor               = &g_SpawnedActors[slot];
        actor->type         = 0x9B;
        actor->pos.x.fixed  = TO_COORD(70);
        actor->header.flags = 1;
        actor->pos.y.fixed  = TO_COORD(52);
    }
}
