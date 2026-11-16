#include "area108_14.h"

MATCH u8 func_801F4F60(s32 x, s32 y) {
    u8  actor_slot;
    s32 i;

    for (i = 0; i < AREA108_TRIGGER_COUNT; i++) {
        if ((u8)x == D_801F63CC[i].x && (u8)y == D_801F63CC[i].y && (D_801F63CC[i].facing & 0xF) == g_Game.members[0].facing) {
            break;
        }
    }
    if (i == AREA108_TRIGGER_COUNT) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x1C) != 0) {
        return 0;
    }
    SYS_ToggleFlag(g_SceneEventFlags, D_801F63CC[i].flag);
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));
    actor_slot = Actor_FindFreeSpawned();
    if (actor_slot != GAME_NONE) {
        SYS_SetFlag(g_SceneEventFlags, 0x1C);
        g_SpawnedActors[actor_slot].type               = 0x18;
        g_SpawnedActors[actor_slot].link               = 0x1B;
        g_SpawnedActors[actor_slot].header.mode        = 0;
        g_SpawnedActors[actor_slot].header.flags       = 1;
        g_SpawnedActors[actor_slot].pos.x.part.integer = D_801F63CC[i].x;
        g_SpawnedActors[actor_slot].pos.y.part.integer = D_801F63CC[i].y;
    }
    return 1;
}
