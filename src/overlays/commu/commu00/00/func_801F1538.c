#include "commu00_00.h"

MATCH s32 func_801F1538(u8* active_ui) {
    g_SceneEventMode        = 23;
    FAIRY_VILLAGE_ACTIVE_UI = active_ui;
    g_SceneEventSelection   = 3;
    Game_SetScriptActive();
    return 0;
}
