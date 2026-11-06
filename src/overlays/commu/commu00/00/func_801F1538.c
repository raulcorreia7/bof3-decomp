#include "commu00_00.h"

MATCH s32 func_801F1538(u8* active_ui) {
    g_SaveData.scene_event.mode      = 23;
    FAIRY_VILLAGE_ACTIVE_UI          = active_ui;
    g_SaveData.scene_event.selection = 3;
    Game_SetScriptActive();
    return 0;
}
