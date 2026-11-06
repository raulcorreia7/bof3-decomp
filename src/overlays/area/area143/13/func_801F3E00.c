#include "area143_13.h"

MATCH s32 func_801F3E00(void) {
    Game_SetScriptActive();
    g_SaveData.scene_event.mode      = 4;
    g_SaveData.scene_event.selection = 0xF;
    if (g_AreaSceneMode == 0) {
        g_AreaSceneMode             = 1;
        g_SaveData.scene_event.step = 5;
    }
    return 0;
}
