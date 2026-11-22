#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F72E4(void) {
    u8*           sub;
    u8            index;
    SpawnedActor* record;

    if (g_GameAreaId == 0x65) {
        sub = &g_ScriptVars[2];
        switch (*sub) {
            case 0:
                if (SYS_TestFlag(g_SceneFlags, 12) == 0) {
                    break;
                }
                if (SYS_TestFlag(g_SceneFlags, 14) != 0) {
                    break;
                }
                Game_SetScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScriptVars[1]          = 0;
                *sub                     = 0;
                g_ScriptVars[3]          = 0;
                g_AreaDrawFlags          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 8;
                switch (g_EmiLoadedCharacterIndex & 0x7F) {
                    case 7:
                        func_801C1E3C(1);
                        func_801C1E3C(0);
                        Scene_RunScenario(0);
                        break;
                    case 8:
                        func_801C1E3C(1);
                        Scene_RunScenario(1);
                        break;
                    case 9:
                        func_801C1E3C(1);
                        func_801C1E3C(2);
                        Scene_RunScenario(0);
                        break;
                    case 10:
                        func_801C1E3C(1);
                        Scene_RunScenario(2);
                        break;
                    case 13:
                        func_801C1E3C(0);
                        Scene_RunScenario(1);
                        break;
                    case 14:
                        func_801C1E3C(0);
                        func_801C1E3C(2);
                        Scene_RunScenario(0);
                        break;
                    case 15:
                        func_801C1E3C(0);
                        Scene_RunScenario(2);
                        break;
                    case 16:
                        func_801C1E3C(2);
                        Scene_RunScenario(1);
                        break;
                    case 18:
                        func_801C1E3C(2);
                        Scene_RunScenario(2);
                        break;
                }
                break;
            case 1:
                g_AreaDrawFlags = 0x1F;
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
        }
    }
    if (g_GameAreaId == 0x82) {
        switch (g_ScriptVars[2]) {
            case 0:
                break;
            case 1:
                g_AreaDrawFlags = 0x1F;
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
                g_AreaDrawFlags = 0x1F;
                g_GameFlags |= 0x16;
                break;
            case 3:
                g_AreaDrawFlags = 0x1F;
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
                g_AreaDrawFlags = 0x1F;
                break;
        }
    }
    if (g_GameAreaId == 0x88) {
        switch (g_ScriptVars[2]) {
            case 0:
                break;
            case 1:
                func_801C1E3C(3);
                break;
            case 2:
                Area_ScrollAdvance(0x200);
                g_AreaCameraRefreshCount = 2;
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
                index = Actor_FindFreeSpawned();
                if (index == 0xFF) {
                    break;
                }
                record               = g_SpawnedActors + index;
                record->header.flags = 1;
                record->type         = 0x77;
                record->header.mode  = 1;
                break;
        }
    }
    if (g_GameAreaId == 0x2D || g_GameAreaId == 0x41 || g_GameAreaId == 0x57 || g_GameAreaId == 0x10 || g_GameAreaId == 0x73) {
        g_ScriptVars[0]          = 0;
        g_ScriptVars[1]          = 0;
        g_ScriptVars[2]          = 0;
        g_ScriptVars[3]          = 0;
        g_ScenarioState.step     = 0;
        g_ScenarioState.state_04 = 0;
    }
    g_ScenarioState.mode_02 = 2;
}
