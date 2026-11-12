#include "area046_13.h"

MATCH void func_801F2C04(void) {
    s8* step = &g_SceneEventStep;
    u8* flag;

    switch (*step) {
        case 0:
            *step = 1;
            break;

        case 1:
            flag = &D_80146865;
            if (*flag != 2) {
                break;
            }
            Game_ClearScriptActive();
            *flag            = 0;
            g_SceneEventMode = SCENE_EVENT_NONE;
            *step            = 0;
            break;

        case 10:
            func_801BE1B0(1);
            *step = 11;
            break;

        case 11:
            if (D_80146865 == 0) {
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                *step            = 0;
            }
            break;
    }
}
