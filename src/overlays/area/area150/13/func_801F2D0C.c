#include "area150_13.h"
#include "menu/save_data.h"

MATCH void func_801F2D0C(void) {
    switch (g_SceneEventState.step) {
        case 10:
            MESSAGE_START_WAIT(MSG_AREA150_ASK_WAIT_FOR_NIGHT);
            g_SceneEventState.step = 11;
            break;
        case 12:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                Game_RequestAreaChange(0xBD, TO_COORD(0x1780), TO_COORD(0xF00), 0xA);
                g_SaveData.return_point.facing = 0xA;
                g_SaveData.desert.reserve      = 0xF0;
                g_SaveData.desert.clock        = 0;
                g_SaveData.desert.days         = 0;
                D_80146880                     = 0;
                D_80146881                     = 0;
                g_SceneEventState.mode         = 0;
                g_SceneEventState.step         = 0;
                g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
                g_ScenarioState.flags_01 |= 1;
            }
            break;
        case 14:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventState.mode = 0;
                g_SceneEventState.step = 0;
            }
            break;
        case 20:
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                if (SYS_TestFlag(g_SaveData.scene_flag_rows[SCENARIO_DESERT_OF_DEATH], 3)) {
                    UI_MessageStartArea(MSG_AREA150_037);
                } else {
                    UI_MessageStartArea(MSG_AREA150_032);
                }
                g_GameStateIndex       = GAME_REQUEST_MESSAGE;
                g_SceneEventState.step = 21;
            }
            break;
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Char_RebuildPartyStats();
                SND_XAStartStream(0, 1);
                g_SceneEventState.step = 22;
            }
            break;
        case 22:
            if (SND_XAIsIdle() & BYTE_MASK) {
                g_ScriptVars[0] = 1;
                SND_BGMStart(0x95, 100, 0x10);
                UI_ModeSet(UI_MODE_FADE_IN);
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                SYS_ClearFlag(g_SaveData.scene_flag_rows[SCENARIO_DESERT_OF_DEATH], 3);
                SYS_ClearFlag(g_SaveData.scene_event_flags, 0x8A);
                g_SceneEventState.mode = 0;
                g_SceneEventState.step = 0;
            }
            break;
    }
}
