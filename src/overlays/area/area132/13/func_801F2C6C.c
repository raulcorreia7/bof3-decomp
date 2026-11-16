#include "area132_13.h"

MATCH void func_801F2C6C(void) {
    u8 actor_slot;

    actor_slot                  = Actor_FindFreeSpawned();
    g_ScratchPad.cells.bytes[0] = actor_slot;
    if (actor_slot == GAME_NONE) {
        return;
    }
    g_SpawnedActors[actor_slot].header.flags                    = ACTOR_FLAG_IN_USE;
    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -902;
    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 226;
    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x1E;
}
