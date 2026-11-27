#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/shared/Area_DrawDimQuad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FBF30(void) {
    u8 v;

    switch (g_ScenarioState.step) {
        case 0:
            g_ScriptVars[2] = 1;
            Game_SetScriptActive();
            g_ScenarioState.step = 1;
            Game_RequestAreaChange(AREA_ID_MCNEIL, TO_COORD(0x15), TO_COORD(0x13), AREA_ENTRY_MAP_LOADING);
            g_GamePrevSelection = 1;
            break;
        case 1: {
            u8* step;

            step                     = &g_ScriptVars[3];
            g_AreaDrawFlags          = 0x1F;
            g_AreaCameraRefreshCount = 2;
            g_AreaCameraOffsetZ -= 0x80;
            v     = *step + 1;
            *step = v;
            if (v != 0x14) {
                break;
            }
            g_AreaCameraOffsetZ      = 0;
            g_AreaCameraRefreshCount = 2;
            *step                    = 0;
            g_ScriptVars[1]          = 0;
            g_ScenarioState.step     = 2;
            break;
        }
        case 2:
            if (g_ScriptVars[0] == 6) {
                Area_ScrollStartRoute(0);
                g_ScenarioState.step = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0x13) {
                SND_SeqStop(0, 1);
                g_ScenarioState.step = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0x1E) {
                SND_BGMPlay(0, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
                g_ScenarioState.step = 5;
            }
            break;
        case 5: {
            u8* vars;

            vars = g_ScriptVars;
            if (vars[0] != 0x28) {
                break;
            }
            Game_SetScriptActive();
            vars[0]              = 0;
            g_ScriptVars[2]      = 2;
            g_ScenarioState.step = 6;
            SYS_SetFlag(g_SceneFlags, 0x3A);
            Game_RequestAreaChange(AREA_ID_MCNEIL, TO_COORD(0x15), TO_COORD(0x13), AREA_ENTRY_MAP_LOADING | FACING_UP);
            break;
        }
        case 6:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            g_ScriptVars[1] = 0;
            g_ScriptVars[2] = 0;
            g_ScriptVars[3] = 0;
            Game_ClearScriptActive();
            SCENARIO_RETURN_TO_START();
            SYS_SetFlag(g_SceneFlags, 0x3B);
            break;
        case 10:
            if (g_ScriptVars[0] != 0xB) {
                break;
            }
            func_801FD28C(0x92);
            g_ScenarioState.step = 0xB;
            g_ScriptVars[0]      = 0xC;
            Scene_SetupParty(2);
            break;
        case 11:
            if (g_ScriptVars[0] == 0xD) {
                func_801FD28C(0x93);
                g_ScenarioState.step = 0xC;
                g_ScriptVars[0]      = 0xE;
            }
            break;
        case 12: {
            u8* step;

            step = &g_ScriptVars[3];
            if (*step == 0x14) {
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                *step           = 0;
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
                SYS_SetFlag(g_SceneFlags, 0x3C);
            } else if (*step == 0x19) {
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                *step           = 0;
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
                SYS_SetFlag(g_SceneFlags, 0x3D);
            }
            break;
        }
        case 13: {
            u8* state;

            state = &g_GameStateIndex;
            if (*state == GAME_REQUEST_MESSAGE) {
                break;
            }
            UI_MessageStartArea(MSG_SCENA01_054);
            *state               = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 0xE;
            break;
        }
        case 14:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScenarioState.step = 0xF;
            }
            break;
        case 15: {
            u8* step;

            step = &g_ScriptVars[3];
            if (*step == 0x14) {
                if ((g_UIWindowChannel & FRONTEND_FLAG_CONFIRM) != 0u) {
                    g_ScriptVars[1] = 0;
                    g_ScriptVars[2] = 0;
                    *step           = 0;
                    Game_ClearScriptActive();
                    SCENARIO_RETURN_TO_START();
                    SYS_SetFlag(g_SceneFlags, 0x3C);
                }
            }
            if (g_ScriptVars[3] == 0x19) {
                if ((g_UIWindowChannel & FRONTEND_FLAG_CONFIRM) != 0u) {
                    g_ScriptVars[1] = 0;
                    g_ScriptVars[2] = 0;
                    g_ScriptVars[3] = 0;
                    Game_ClearScriptActive();
                    SCENARIO_RETURN_TO_START();
                    SYS_SetFlag(g_SceneFlags, 0x3D);
                }
            }
            break;
        }
        case 16: {
            u8* state;

            state = &g_GameStateIndex;
            if (*state == GAME_REQUEST_MESSAGE) {
                break;
            }
            UI_MessageStartArea(MSG_SCENA01_054);
            *state               = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 0x11;
            break;
        }
        case 17:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScenarioState.step = 0x12;
            }
            break;
        case 18: {
            u8* step;

            step = &g_ScriptVars[3];
            if (*step == 0x14) {
                if ((g_UIWindowChannel & FRONTEND_FLAG_CONFIRM) != 0u) {
                    g_ScriptVars[0] = 0;
                    g_ScriptVars[1] = 0;
                    g_ScriptVars[2] = 0;
                    *step           = 0;
                    Game_ClearScriptActive();
                    SCENARIO_RETURN_TO_START();
                    SYS_SetFlag(g_SceneFlags, 0x3C);
                }
            }
            if (g_ScriptVars[3] == 0x19) {
                if ((g_UIWindowChannel & FRONTEND_FLAG_CONFIRM) != 0u) {
                    g_ScriptVars[0] = 0;
                    g_ScriptVars[1] = 0;
                    g_ScriptVars[2] = 0;
                    g_ScriptVars[3] = 0;
                    Game_ClearScriptActive();
                    SCENARIO_RETURN_TO_START();
                    SYS_SetFlag(g_SceneFlags, 0x3D);
                }
            }
            break;
        }
    }
}
