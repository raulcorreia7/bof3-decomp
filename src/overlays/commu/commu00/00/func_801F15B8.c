#include "commu00_00.h"

MATCH s32 func_801F15B8(u8* active_ui) {
    FAIRY_VILLAGE_ACTIVE_UI     = active_ui;
    g_SceneEventState.mode      = 60;
    g_SceneEventState.selection = active_ui[5];
    Game_SetScriptActive();
    return 0;
}
