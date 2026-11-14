#include "area071_13.h"
#include "game/spawn.h"

MATCH void func_801F2CF4(void) {
    u8 index;

    index                  = Actor_FindFreeSlot();
    D_1F800000.view.raw[0] = index;
    if (index != GAME_NONE) {
        g_SpawnedActors[index].header.flags          = 1;
        g_SpawnedActors[D_1F800000.view.raw[0]].type = 0x25;
    }
}
