#include "area193_13.h"
#include "menu/save_data.h"

MATCH void func_801F2EA0(void) {
    switch (g_SceneEventState.step) {
        case 0:
            break;
        case 10:
            MESSAGE_START_WAIT(MSG_AREA193_ASK_LEAVE_DESERT);
            g_SceneEventState.step = 0xB;
            break;
        case 12:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                u8* flag;

                SYS_ClearFlag(g_SceneEventFlags, 0x77);
                Game_ClearScriptActive();
                Game_RequestAreaChange(AREA_ID_DESERT_OF_DEATH_MAP, TO_COORD(0x1200), TO_COORD(0x17FF), FACING_UP_RIGHT);
                g_SaveData.return_point.facing = 2;
                g_SaveData.desert.reserve      = 0xF0;
                g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
                g_SaveData.desert.clock = 0;
                g_SaveData.desert.days  = 0;
                D_80146880              = 0;
                D_80146881              = 0;
                g_SceneEventState.mode  = SCENE_EVENT_NONE;
                g_SceneEventState.step  = 0;
                flag                    = &g_ScenarioState.flags_01;
                *flag |= 1;
            }
            break;
        case 14:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SYS_ClearFlag(g_SceneEventFlags, 0x77);
                Game_ClearScriptActive();
                Game_RequestAreaChange(AREA_ID_KOMBINAT_WORLD_MAP, TO_COORD(0x16), TO_COORD(0x15), FACING_RIGHT);
                g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
        case 16:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
        case 20:
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                MESSAGE_START_WAIT(SYS_TestFlag(&g_Scenario2Flags[0x60], 3) ? 0x25 : 0x20);
                g_SceneEventState.step = 0x15;
            }
            break;
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Char_RebuildPartyStats();
                SND_XAStartStream(0, 1);
                g_SceneEventState.step = 0x16;
            }
            break;
        case 22:
            if ((SND_XAIsIdle() & BYTE_MASK) != 0) {
                u8* flags;

                g_ScriptVars[0] = 1;
                SND_BGMStart(0x95, 100, 0x10);
                UI_ModeSet(UI_MODE_FADE_IN);
                flags           = &g_Scenario2Flags[0x60];
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                SYS_ClearFlag(flags, 3);
                SYS_ClearFlag(flags + 0x30, 0x8A);
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
    }
}
