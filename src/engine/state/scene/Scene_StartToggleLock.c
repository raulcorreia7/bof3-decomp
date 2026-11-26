#include "engine/game/00/game_00.h"

/* K&R call keeps a0 undisturbed; the callee ignores the argument. */

/* func_8019ABB0 */
/* Sets scene flag 28 and spawns the actor that clears it after the given frames. */
MATCH void Scene_StartToggleLock(s32 frames) {
    u8 index;

    index = Actor_FindFreeSpawned() & BYTE_MASK;
    if (index != GAME_NONE) {
        g_SpawnedActors[index].header.flags = 1;
        g_SpawnedActors[index].type         = 4;
        g_SpawnedActors[index].layer        = frames;
        SYS_SetFlag(g_SceneEventFlags, 28);
    }
}
