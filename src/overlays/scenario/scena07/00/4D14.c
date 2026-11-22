#include "scena07_00.h"

#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FB914(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            Game_ClearScriptActive();
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x20);
            g_ScenarioState.step_05 = 2;
            break;
        default:
            break;
    }
}
#else
INCLUDE_ASM(func_801FB914);
#endif

MATCH void func_801FC094(void) {
    u8 i;
    u8 slot_index;

    for (i = 0; i < ARRAY_COUNT(D_801FDE40); i++) {
        if (D_801FDE40[i].timer != g_ScenarioState.timer_06) {
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
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2) + i % 3);
    }
}

MATCH void func_801FC1C4(void) {
    u8* step;

    step = &g_ScenarioState.step_05;
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
                g_ScenarioState.state_04 = 0;
                *step                    = 0;
            }
            break;
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801FC2D0(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
        case 13:
            break;
        case 14:
            break;
        case 15:
            break;
        case 16:
            break;
        case 17:
            break;
        case 18:
            break;
        case 19:
            break;
        case 20:
            break;
        case 21:
            break;
        case 22:
            break;
        case 23:
            break;
        case 24:
            break;
        case 25:
            break;
        case 26:
            break;
        case 27:
            break;
        case 28:
            break;
        case 29:
            break;
        case 30:
            break;
        case 31:
            break;
        case 32:
            break;
        case 33:
            break;
        case 34:
            break;
        case 35:
            break;
        case 36:
            break;
        case 37:
            break;
        case 38:
            break;
        case 39:
            break;
    }
}
#else
INCLUDE_ASM(func_801FC2D0);
#endif

MATCH void func_801FCFB4(void) {
    u8 cam                   = D_801FDE88[g_FrameCount & 0x3];
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = g_AreaCameraOffsetY + ((cam << 24) >> 22);
}

MATCH void func_801FD000(void) {
    u8 i;
    u8 idx;

    for (i = 0; i < 0xE; i++) {
        g_ScratchPad.cells.halves[0] = Actor_FindFreeField();
        if (g_ScratchPad.cells.halves[0] != GAME_NONE) {
            idx = i;
            Actor_SpawnFromRecord(&D_801FDE8C[idx * 17]);
            g_Task->pos.z.part.integer = 0xA00;
            if (D_801FDF7C[idx] != 0) {
                g_CurrentActor->timer_75 = D_801FDF7C[idx];
                g_Task->unk_03           = g_Task->header.mode;
                g_Task->header.mode      = 5;
            }
        }
    }
}
