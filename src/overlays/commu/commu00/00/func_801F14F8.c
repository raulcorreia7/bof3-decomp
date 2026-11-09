#include "commu00_00.h"

MATCH s32 func_801F14F8(u8* active_ui) {
    FAIRY_VILLAGE_ACTIVE_UI = active_ui;
    g_SceneEventMode        = 0x17;
    Game_SetScriptActive();
    D_801448F2 = 1;
    return 0;
}
