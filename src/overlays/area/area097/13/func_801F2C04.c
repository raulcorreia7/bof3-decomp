#include "area097_13.h"

MATCH void func_801F2C04(void) {
    u8* result;
    s8* state = &g_SceneEventStep;

    switch (*state) {
        case 0:
            Game_SetScriptActive();
            *state = 1;
            break;
        case 1:
            result = &D_80146867;
            if (*result == 2) {
                Game_ClearScriptActive();
                *result          = 0;
                g_SceneEventMode = SCENE_EVENT_NONE;
                *state           = 0;
            }
            break;
    }
}
