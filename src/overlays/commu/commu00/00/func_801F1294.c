#include "commu00_00.h"

MATCH s32 func_801F1294(u8* active_ui) {
    FAIRY_VILLAGE_ACTIVE_UI = active_ui;
    g_SceneEventMode        = 14;
    Game_SetScriptActive();
    return 0;
}
