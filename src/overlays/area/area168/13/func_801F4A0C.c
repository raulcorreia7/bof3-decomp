#include "area168_13.h"

MATCH void func_801F4A0C(void) {
    switch (g_SceneEventStep) {
        case 0:
            if (g_GameStateIndex != 2) {
                g_SceneEventStep = 1;
            }
            break;
        case 1:
            Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, 0xB0000, 0x698000, 0x89);
            g_SceneEventMode = SCENE_EVENT_NONE;
            g_SceneEventStep = 0;
            break;
        case 10:
            func_801C601C(0);
            g_SceneEventStep = 11;
            break;
        case 11:
            if (g_ScriptVars[0] == 1) {
                SND_PlayCue(0x204);
                SYS_SetFlag(g_SceneEventFlags, 145);
                g_SceneEventStep = 12;
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 2) {
                Game_ClearScriptActive();
                g_ScriptVars[0]  = 0;
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
    }
}
