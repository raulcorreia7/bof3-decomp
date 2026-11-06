#include "commu00_00.h"

MATCH s32 func_801F14C4(u8* active_ui) {
    FAIRY_VILLAGE_ACTIVE_UI = active_ui;
    g_SceneEventMode        = 23;
    Game_SetScriptActive();
    return 0;
}
