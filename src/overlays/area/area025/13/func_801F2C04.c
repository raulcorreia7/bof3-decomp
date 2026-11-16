#include "area025_13.h"
#include "game/spawn.h"

MATCH void func_801F2C04(void) {
    u8 actor_slot;

    if (g_FrameCount & 0x3) {
        return;
    }
    actor_slot                  = Actor_FindFreeSpawned();
    g_ScratchPad.cells.bytes[0] = actor_slot;
    if (actor_slot == GAME_NONE) {
        return;
    }
    g_SpawnedActors[actor_slot].header.flags                = 1;
    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type       = 0xB;
    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].counter_1C = 6;
    if (g_ScriptVars[2] < 0x14) {
        g_SpawnedActors[g_ScratchPad.cells.bytes[0]].unk_07 = 1;
    } else {
        g_SpawnedActors[g_ScratchPad.cells.bytes[0]].unk_07 = 3;
    }
}
