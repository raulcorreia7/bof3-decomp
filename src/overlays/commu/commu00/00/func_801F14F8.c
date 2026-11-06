#include "commu00_00.h"

MATCH s32 func_801F14F8(u8* active_ui) {
    /* FAKE: flag value pinned to v1. */
    MATCH_REG(u8, flag, "v1");

    FAIRY_VILLAGE_ACTIVE_UI = active_ui;
    g_SceneEventMode        = 0x17;
    Game_SetScriptActive();
    flag       = 1;
    D_801448F2 = flag;
    return 0;
}
