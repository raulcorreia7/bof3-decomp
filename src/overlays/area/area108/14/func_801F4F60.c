#include "area108_14.h"

#ifdef NON_MATCHING
NON_MATCHING u8 func_801F4F60(s32 x, s32 y) {
    u8  actor_slot;
    s32 i;
    s32 offset;

    for (i = 0; i < 4; i++) {
        if ((u8)x == D_801F63CC[i].x && (u8)y == D_801F63CC[i].y && (D_801F63CC[i].facing & 0xF) == g_Game.members[0].facing) {
            break;
        }
    }
    if (i == 4) {
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
        D_80143FCD[actor_slot * ACTOR_SLOT_SIZE]       = 0x18;
        D_80143FD3[actor_slot * ACTOR_SLOT_SIZE]       = 0x1B;
        D_80143FC9[actor_slot * ACTOR_SLOT_SIZE]       = 0;
        D_80143FC8[actor_slot * ACTOR_SLOT_SIZE]       = 1;
        D_80143FFE[actor_slot * (ACTOR_SLOT_SIZE / 2)] = D_801F63CC[i].x;
        D_80144002[actor_slot * (ACTOR_SLOT_SIZE / 2)] = D_801F63CC[i].y;
    }
    return 1;
}
#else
INCLUDE_ASM(func_801F4F60);
#endif
