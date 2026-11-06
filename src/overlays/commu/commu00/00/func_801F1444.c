#include "commu00_00.h"

MATCH s32 func_801F1444(u8* active_ui) {
    FAIRY_VILLAGE_ACTIVE_UI          = active_ui;
    g_SaveData.scene_event.mode      = 21;
    g_SaveData.scene_event.selection = active_ui[5];
    Game_SetScriptActive();
    return 0;
}
