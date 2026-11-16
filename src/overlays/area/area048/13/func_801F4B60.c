#include "area048_13.h"

MATCH void func_801F4B60(void) {
    u8* selector;
    u32 cue;

    selector = &g_SceneEventState.selection;
    if (*selector == 1) {
        switch (D_8014686B) {
            case 8:
                cue = 1;
                break;
            case 6:
                cue = 7;
                break;
            case 2:
                cue = 6;
                break;
            default:
                cue = 8;
                break;
        }
        Scene_SetupParty(cue);
    } else {
        if (*selector == 0) {
            Scene_SetupParty(0);
        }
        if (*selector == 2) {
            Scene_SetupParty(2);
        }
    }
    Game_ClearScriptActive();
    g_SceneEventState.mode      = 0;
    g_SceneEventState.step      = 0;
    g_SceneEventState.selection = 0;
}
