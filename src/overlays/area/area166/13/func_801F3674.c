#include "area166_13.h"

MATCH void func_801F3674(void) {
    u8* record;

    MESSAGE_REQUEST_CLEAR();
    if (g_MessageChoice == 3) {
        Game_SetScriptActive();
        g_SceneEventMode      = SCENE_EVENT_SHOP_SAVE;
        g_SceneEventStep      = 0x5;
        g_SceneEventSelection = 0xFF;
    }
    record                    = (u8*)g_ScriptWorkRecord;
    FIELD(s32, record, 0x18U) = D_801F3940[g_MessageChoice * 2];
    /* FAKE: retail reloads the selection byte after the 0x18 store. */
    MATCH_FAKE_BARRIER();
    FIELD(s32, record, 0x1CU) = D_801F3941[g_MessageChoice * 2];
}
