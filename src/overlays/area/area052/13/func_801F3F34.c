#include "area052_13.h"
#include "menu/save_data.h"

MATCH void func_801F3F34(void) {
    switch (g_SceneEventStep) {
        case 0:
            g_ScriptVars[3]              = 1;
            g_SaveData.scene_event_timer = 16;
            g_SceneEventStep             = 1;
            D_801F5071                   = 0;
            break;

        case 1:
            if (--g_SaveData.scene_event_timer < 4) {
                g_ScriptVars[3]  = 0;
                g_SceneEventStep = 2;
            }
            break;

        case 2:
            if (--g_SaveData.scene_event_timer == 0) {
                SYS_ClearFlag(g_SaveData.scene_event_flags, 0x24);
                D_801F5071 = -1;
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;

        case 10:
            Message_StartAreaMessage(57);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            g_SceneEventStep = 11;
            break;

        case 11:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;

        case 20:
            g_ScriptVars[3]              = 10;
            g_SaveData.scene_event_timer = 16;
            D_801F5071                   = 0;
            g_SceneEventStep             = 21;
            break;

        case 21:
            if (--g_SaveData.scene_event_timer < 4) {
                g_ScriptVars[3]  = 0;
                g_SceneEventStep = 22;
            }
            break;

        case 22:
            if (--g_SaveData.scene_event_timer == 0) {
                SYS_ClearFlag(g_SaveData.scene_event_flags, 0x26);
                D_801F5071 = -1;
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;

        case 40:
            g_ScriptVars[3]              = 20;
            g_SaveData.scene_event_timer = 16;
            D_801F5071                   = 0;
            g_SceneEventStep             = 41;
            break;

        case 41:
            if (--g_SaveData.scene_event_timer < 4) {
                g_ScriptVars[3]  = 0;
                g_SceneEventStep = 42;
            }
            break;

        case 42:
            if (--g_SaveData.scene_event_timer == 0) {
                SYS_ClearFlag(g_SaveData.scene_event_flags, 0x25);
                D_801F5071 = -1;
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;

        case 45:
            g_ScriptVars[3]  = 0;
            g_SceneEventStep = 46;
            break;

        case 46:
            if (g_ScriptVars[3] == 30) {
                func_801F3D24();
                g_SceneEventStep = 47;
            }
            break;

        case 47:
            if (g_ScriptVars[3] == 40) {
                Area_StoreHeight(134, 17, 0);
                Area_SetCellCode(134, 17, 0);
                Area_StoreHeight(134, 18, 0);
                Area_SetCellCode(134, 18, 0);
                Area_StoreHeight(135, 17, 0);
                Area_SetCellCode(135, 17, 16);
                Area_StoreHeight(135, 18, 0);
                Area_SetCellCode(135, 18, 16);
                g_SaveData.scene_event_timer = 10;
                g_SceneEventStep             = 41;
            }
            break;
    }
}
