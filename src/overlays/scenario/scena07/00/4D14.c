#include "scena07_00.h"

#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801FB914);

MATCH void func_801FC094(void) {
    u8 i;
    u8 slot_index;

    for (i = 0; i < ARRAY_COUNT(D_801FDE40); i++) {
        if (D_801FDE40[i].timer != g_SceneState.timer_06) {
            continue;
        }
        slot_index = Actor_FindFreeSpawned();
        if (slot_index == GAME_NONE) {
            break;
        }
        g_SpawnedActors[slot_index].header.flags     = 1;
        g_SpawnedActors[slot_index].type             = 0x18;
        g_SpawnedActors[slot_index].link             = 0x18;
        COORD_INT(g_SpawnedActors[slot_index].pos.x) = D_801FDE40[i].x;
        COORD_INT(g_SpawnedActors[slot_index].pos.y) = D_801FDE40[i].y;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2) + i % 3);
    }
}

MATCH void func_801FC1C4(void) {
    u8* step;

    step = &g_SceneState.step_05;
    switch (*step) {
        case 0:
            func_8019FA28(0x35, 0x120000, 0x180000, 1);
            g_GamePrevSelection = 0x4D;
            *step               = 1;
            break;
        case 1:
            if (g_UiWindowEffectBusy == 0) {
                *step = 2;
            }
            break;
        case 2:
            if (*g_ScriptVars == 9) {
                SYS_SetFlag(g_SceneFlags, 7);
                func_8019FA28(0x58, 0x350000, 0x230000, 3);
                g_GameFlags &= ~GAME_FLAG_SCROLL_LOCK;
                Game_ClearScriptActive();
                g_SceneState.state_04 = 0;
                *step                 = 0;
            }
            break;
    }
}

INCLUDE_ASM(func_801FC2D0);

MATCH void func_801FCFB4(void) {
    u8 cam                   = D_801FDE88[g_FrameCount & 0x3];
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = g_AreaCameraOffsetY + ((cam << 24) >> 22);
}

MATCH void func_801FD000(void) {
    u8 i;
    u8 idx;

    for (i = 0; i < 0xE; i++) {
        D_1F800000.cells.halves[0] = Actor_FindFreeField();
        if (D_1F800000.cells.halves[0] != GAME_NONE) {
            idx = i;
            func_801A4D54(&D_801FDE8C[idx * 17]);
            g_Task->pos.z.part.integer = 0xA00;
            if (D_801FDF7C[idx] != 0) {
                g_CurrentActor->timer_75 = D_801FDF7C[idx];
                g_Task->unk_03           = g_Task->header.mode;
                g_Task->header.mode      = 5;
            }
        }
    }
}
