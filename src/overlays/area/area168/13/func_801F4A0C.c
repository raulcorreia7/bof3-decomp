#include "area168_13.h"

MATCH void func_801F4A0C(void) {
    switch (g_SceneEventState.step) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_SceneEventState.step = 1;
            }
            break;
        case 1:
            Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, 0xB0000, 0x698000, 0x89);
            g_SceneEventState.mode = SCENE_EVENT_NONE;
            g_SceneEventState.step = 0;
            break;
        case 10:
            Area_StartScrollRoute(0);
            g_SceneEventState.step = 11;
            break;
        case 11:
            if (g_ScriptVars[0] == 1) {
                SND_SEPlay(0x204);
                SYS_SetFlag(g_SceneEventFlags, 145);
                g_SceneEventState.step = 12;
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 2) {
                Game_ClearScriptActive();
                g_ScriptVars[0]        = 0;
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
    }
}
