#include "area143_13.h"

MATCH s32 func_801F3E00(void) {
    Game_SetScriptActive();
    g_SceneEventMode      = 4;
    g_SceneEventSelection = 0xF;
    if (g_AreaSceneMode == 0) {
        g_AreaSceneMode  = 1;
        g_SceneEventStep = 5;
    }
    return 0;
}
