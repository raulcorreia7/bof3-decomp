#include "area143_13.h"

MATCH s32 func_801F3E00(void) {
    Game_SetScriptActive();
    g_SceneEventState.mode      = SCENE_EVENT_MASTER;
    g_SceneEventState.selection = 0xF;
    if (g_AreaSceneMode == 0) {
        g_AreaSceneMode        = 1;
        g_SceneEventState.step = 5;
    }
    return 0;
}
