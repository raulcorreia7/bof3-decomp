#include "scena14_00.h"
#include "menu/save_data.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7BA0(void) {
    switch (g_ScenarioState.step) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 0;
                Scene_SetupParty(1);
                g_ScenarioState.step = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 1) {
                u8* flags;

                SYS_SetFlag(g_SceneFlags, 1);
                Game_RequestAreaChange(AREA_ID_DESERT_OF_DEATH_MAP, TO_COORD(0x1000), TO_COORD(0x1400), FACING_UP_RIGHT);
                flags                          = &g_ScenarioState.flags_01;
                g_SaveData.return_point.facing = 2;
                g_SaveData.desert.clock        = 0;
                g_ScenarioState.step           = 2;
                g_GamePrevSelection            = g_SndBGMId;
                *flags |= 1;
            }
            break;
        case 2:
            if (!WINDOW_EFFECT_BUSY()) {
                SCENARIO_MESSAGE_WAIT(MSG_SCENA14_018, 3);
            }
            break;
        case 3:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Scene_SpawnActor(0x13, g_AreaCameraAngle.vx, g_AreaCameraAngle.vy, -0x200, 0x20, 0);
                g_ScenarioState.step = 4;
            } else {
                UI_CursorDraw(0x98, 0x28, 0);
            }
            break;
        case 4:
            if (!(g_SpawnedActors[D_801FC4C0].header.flags & 1)) {
                SCENARIO_MESSAGE_WAIT(MSG_SCENA14_019, 5);
            }
            break;
        case 5:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Scene_SpawnActor(0x13, g_AreaCameraAngle.vx, g_AreaCameraAngle.vy, 0x400, 0x20, 0);
                g_ScenarioState.step = 6;
            } else {
                UI_CursorDraw(0x98, 0x38, 0);
            }
            break;
        case 6:
            if (!(g_SpawnedActors[D_801FC4C0].header.flags & 1)) {
                SCENARIO_MESSAGE_WAIT(MSG_SCENA14_020, 7);
            }
            break;
        case 7:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                u8* flags;

                Game_ClearScriptActive();
                SYS_ClearFlag(g_SceneFlags, 1);
                Game_RequestAreaChange(AREA_ID_DESERT_ENTRANCE_CAMP, TO_COORD_HALF(26), TO_COORD(28), AREA_ENTRY_MAP_LOADING | FACING_UP_RIGHT);
                flags                    = &g_ScenarioState.flags_01;
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
                *flags &= ~1;
            } else {
                UI_CursorDraw(0x98, 0x10, 0);
            }
            break;
        case 20:
        case 25:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                if (g_ScenarioState.step == 20) {
                    SYS_ClearFlag(g_SceneEventFlags, 0x77);
                    g_SaveData.return_point.pending = 0;
                    Game_RequestAreaChange(AREA_ID_DESERT_ENTRANCE_CAMP, TO_COORD_HALF(26), TO_COORD(28), AREA_ENTRY_MAP_LOADING | FACING_RIGHT);
                } else {
                    SYS_SetFlag(g_SceneFlags, 2);
                    SYS_SetFlag(g_SceneFlags, 3);
                    Game_RequestAreaChange(AREA_ID_DESERT_ENTRANCE_CAMP, TO_COORD_HALF(26), TO_COORD(28), AREA_ENTRY_MAP_LOADING | FACING_DOWN_RIGHT);
                    g_GameEntryMode = 0xFF;
                }
                SYS_SetFlag(g_SceneEventFlags, 0x8A);
                g_GameRequestType        = GAME_NONE;
                g_GamePrevSelection      = GAME_NONE;
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.flags_01 &= ~1;
            }
            break;
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 21:
        case 22:
        case 23:
        case 24:
            break;
    }
}
