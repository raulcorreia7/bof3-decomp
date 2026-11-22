#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7F78(void) {
    u8 slot;

    if (g_GameAreaId == 0x65) {
        switch (g_ScriptVars[2]) {
            case 0:
                break;
            case 1:
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                break;
            case 2:
                g_AreaDrawFlags = 0;
                break;
        }
    }
    if (g_GameAreaId == 0x79) {
        switch (g_ScriptVars[2]) {
            case 0:
                break;
            case 1:
                g_AreaDrawFlags = 0;
                break;
            case 2:
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                Game_ClearScriptActive();
                SCRIPT_VARS_CLEAR_ALL();
                break;
        }
    }
    if (g_GameAreaId == 0x82) {
        switch (g_ScriptVars[2]) {
            case 0:
                break;
            case 1:
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                break;
        }
    }
    if (g_GameAreaId == 0x83) {
        switch (g_ScriptVars[2]) {
            case 0:
                break;
            case 1:
                Area_ScrollAdvance(0x498);
                g_AreaCameraRefreshCount = 2;
                break;
            case 2:
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                g_GameFlags |= 0x16;
                break;
            case 3:
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                break;
        }
    }
    if (g_GameAreaId == 0x84) {
        switch (g_ScriptVars[2]) {
            case 0:
                break;
            case 1:
                g_AreaDrawFlags = 0;
                g_GameFlags |= 0x16;
                break;
            case 2:
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                break;
        }
    }
    if (g_GameAreaId == 0x85) {
        if (SYS_TestFlag(g_SceneFlags, 0x24) && !SYS_TestFlag(g_SceneFlags, 0x26) && g_GameCellType == 2) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 0x19;
            g_ScenarioState.state_04 = 5;
        }
        switch (g_ScriptVars[2]) {
            case 0:
            case 1:
            case 2:
            case 4:
                break;
            case 3:
                g_GameFlags |= 0xE;
                switch (g_EmiLoadedCharacterIndex & 0x7F) {
                    case 7:
                        break;
                    case 8:
                        func_801C1E3C(1);
                        Scene_RunScenario(3);
                        break;
                    case 13:
                        func_801C1E3C(0);
                        Scene_RunScenario(3);
                        break;
                    case 16:
                        func_801C1E3C(2);
                        Scene_RunScenario(3);
                        break;
                    case 17:
                        func_801C1E3C(4);
                        Scene_RunScenario(9);
                        break;
                    case 18:
                        break;
                }
                break;
            case 10:
                slot = Actor_FindFreeSpawned();
                if (slot != GAME_NONE) {
                    SpawnedActor* spawned = &g_SpawnedActors[slot];

                    spawned->header.flags = 1;
                    spawned->type         = 0x77;
                    spawned->header.mode  = 1;
                }
                break;
        }
    }
    if (g_GameAreaId == 0x86) {
        if (!SYS_TestFlag(g_SceneFlags, 0x2F) && g_Game.members[0].pos.x.fixed < 0x300000) {
            SYS_SetFlag(g_SceneFlags, 0x2F);
            Game_SetScriptActive();
            SCRIPT_VARS_CLEAR_ALL();
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 9;
        }
    }
    if (g_GameAreaId == 0x87) {
        switch (g_ScriptVars[2]) {
            case 0:
                break;
            case 10:
                slot = Actor_FindFreeSpawned();
                if (slot != GAME_NONE) {
                    SpawnedActor* spawned = &g_SpawnedActors[slot];

                    spawned->header.flags = 1;
                    spawned->type         = 0x77;
                    spawned->header.mode  = 1;
                }
                break;
        }
    }
    if (g_GameAreaId == 0x88) {
        switch (g_ScriptVars[2]) {
            case 0:
            case 3:
                break;
            case 1:
                func_801C1E3C(3);
                break;
            case 2:
                Area_ScrollAdvance(0x200);
                g_AreaCameraRefreshCount = 2;
                break;
            case 10:
                slot = Actor_FindFreeSpawned();
                if (slot != GAME_NONE) {
                    SpawnedActor* spawned = &g_SpawnedActors[slot];

                    spawned->header.flags = 1;
                    spawned->type         = 0x77;
                    spawned->header.mode  = 1;
                }
                break;
        }
    }
    if (g_GameAreaId == 0xBC) {
        switch (g_ScriptVars[2]) {
            case 0:
                break;
            case 1:
                if (!SYS_TestFlag(g_SceneFlags, 0x28)) {
                    slot                        = Actor_FindFreeSpawned();
                    g_ScratchPad.cells.bytes[0] = slot;
                    if ((slot & BYTE_MASK) != GAME_NONE) {
                        g_SpawnedActors[slot].header.flags                = 1;
                        g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x76;
                    }
                }
                break;
            case 2:
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x79;
                }
                SND_BGMRequest(0x8F);
                while (!EMI_IsReady()) {
                    SYS_ThreadWait(1);
                }
                SND_BGMPlay(0x8F, 100, 8);
                break;
            case 3:
                g_GameFlags |= 8;
                Area_ScrollAdvance(0x290);
                g_AreaCameraRefreshCount = 2;
                break;
            case 4:
                Area_ScrollAdvance(0x100);
                g_AreaCameraRefreshCount = 2;
                break;
            case 5:
                func_801C1E3C(2);
                func_801C1E3C(3);
                Scene_RunScenario(8);
                break;
            case 6:
                g_AreaDrawFlags             = AREA_DRAW_ALL_FLAGS;
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x7B;
                }
                break;
            case 7:
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x7B;
                }
                break;
            case 8:
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x7C;
                }
                break;
            case 9:
                SND_BGMRequest(0x8B);
                while (!EMI_IsReady()) {
                    SYS_ThreadWait(1);
                }
                SND_BGMPlay(0x8B, 100, 8);
                break;
        }
    }
    if (g_GameAreaId == 0x2D || g_GameAreaId == 0x41 || g_GameAreaId == 0x57 || g_GameAreaId == 0x10 || g_GameAreaId == 0x73) {
        SCRIPT_VARS_CLEAR_ALL();
        g_ScenarioState.step_05  = 0;
        g_ScenarioState.state_04 = 0;
    }
    D_80146872 = 2;
}
