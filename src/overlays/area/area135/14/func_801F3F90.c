#include "area135_14.h"

MATCH void func_801F3F90(void) {
    u8 answer;

    if (g_UIMessageChoice != 0) {
        if (g_UIMessageChoice == 1) {
            answer = 1;
        } else {
            g_UIMessageRequest = MESSAGE_NONE;
            return;
        }
    } else {
        answer = 0;
    }

    Game_SetScriptActive();
    g_SceneEventMode = 0x12;
    g_SceneEventStep = 0x14;
    g_SceneActorSlot = Actor_FindFreeSpawned();
    if (g_SceneActorSlot != GAME_NONE) {
        g_SpawnedActors[g_SceneActorSlot].header.flags = 1;
        g_SpawnedActors[g_SceneActorSlot].type         = 0x66;
        g_SpawnedActors[g_SceneActorSlot].unk_06       = answer;
    }
    g_UIMessageRequest = MESSAGE_NONE;
}
