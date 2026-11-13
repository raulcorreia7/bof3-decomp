#include "area046_13.h"

MATCH void func_801F2C04(void) {
    s8* step = &g_SceneEventStep;
    u8* script_var;

    switch (*step) {
        case 0:
            *step = 1;
            break;

        case 1:
            script_var = &g_ScriptVars[1];
            if (*script_var != 2) {
                break;
            }
            Game_ClearScriptActive();
            *script_var      = 0;
            g_SceneEventMode = SCENE_EVENT_NONE;
            *step            = 0;
            break;

        case 10:
            func_801BE1B0(1);
            *step = 11;
            break;

        case 11:
            if (g_ScriptVars[1] == 0) {
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                *step            = 0;
            }
            break;
    }
}
