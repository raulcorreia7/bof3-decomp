#include "scena01_00.h"
#include "area/map.h"
#include "menu/panel.h"
#include "shared/etc.h"
#include "overlays/area/Area_DrawDimQuad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FBB1C(void) {
    u8 slot;

    switch (g_ScenarioState.step_05) {
        case 0:
            g_ScriptVars[2]         = 1;
            g_ScenarioState.step_05 = 1;
            g_GameFlags ^= 0x20;
            Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_HOUSE, TO_COORD(0x30), TO_COORD(1), 0);
            g_GamePrevSelection = 0xFF;
            break;
        case 1:
            g_ScriptVars[0] = 1;
            Area_StartScrollRoute(0);
            g_ScenarioState.step_05 = 2;
            break;
        case 2:
            if (g_ScriptVars[0] == 2) {
                UI_SetMode(UI_MODE_LONG_FADE_IN);
                g_AreaDrawFlags         = 0x1F;
                g_ScenarioState.step_05 = 3;
            }
            break;
        case 3:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            SND_PlayBGM(8, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_ScenarioState.step_05 = 4;
            break;
        case 4:
            if (g_ScriptVars[0] == 5) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                          = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0xE3;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x40;
                    g_ScenarioState.step_05                                     = 5;
                }
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 6) {
                if (Area_TurnCameraX(-0x50, -2) == 0) {
                    g_ScenarioState.step_05 = 6;
                }
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 8) {
                UI_SetMode(UI_MODE_LONG_FADE_OUT);
                g_ScenarioState.step_05 = 7;
            }
            break;
        case 7:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            g_ScriptVars[0] = 9;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA01_004, 8);
            break;
        case 8:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScriptVars[2]         = 2;
            g_ScenarioState.step_05 = 9;
            SYS_SetFlag(g_SceneFlags, 0x15);
            Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_HOUSE, TO_COORD(0x54), TO_COORD(0x25), 0x81);
            break;
        case 9:
            if (g_ScriptVars[0] == 0x14) {
                g_ScriptVars[2]         = 3;
                g_ScenarioState.step_05 = 0xA;
                SYS_SetFlag(g_SceneFlags, 0x16);
                Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_HOUSE, TO_COORD(0x10), TO_COORD(0xD), 0x82);
            }
            break;
        case 10:
            Game_ClearScriptActive();
            Char_RebuildPartyStats();
            SCRIPT_VARS_CLEAR_ALL();
            SCENARIO_RETURN_TO_START();
            break;
    }
}
