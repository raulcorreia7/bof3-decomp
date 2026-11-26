#include "scena15_00.h"
#include "menu/save_data.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA9DC(void) {
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

                SYS_SetFlag(&g_SceneFlagWords[14 * 8], 1);
                func_8019FA28(0xBD, TO_COORD(0x1000), TO_COORD(0x1400), 2);
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
                SCENARIO_MESSAGE_WAIT(MSG_SCENA15_018, 3);
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
            if (!(g_SpawnedActors[D_801FE748].header.flags & 1)) {
                SCENARIO_MESSAGE_WAIT(MSG_SCENA15_019, 5);
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
            if (!(g_SpawnedActors[D_801FE748].header.flags & 1)) {
                SCENARIO_MESSAGE_WAIT(MSG_SCENA15_020, 7);
            }
            break;
        case 7:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                u8* flags;

                Game_ClearScriptActive();
                SYS_ClearFlag(&g_SceneFlagWords[14 * 8], 1);
                func_8019FA28(0xC1, 0x1A8000, 0x1C0000, 0x82);
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
                    func_8019FA28(0xC1, 0x1A8000, 0x1C0000, 0x83);
                } else {
                    SYS_SetFlag(&g_SceneFlagWords[14 * 8], 2);
                    SYS_SetFlag(&g_SceneFlagWords[14 * 8], 3);
                    func_8019FA28(0xC1, 0x1A8000, 0x1C0000, 0x84);
                    g_GameEntryMode = 0xFF;
                }
                SYS_SetFlag(g_SceneEventFlags, 0x8A);
                D_80143F1D               = 0xFF;
                g_GamePrevSelection      = 0xFF;
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
