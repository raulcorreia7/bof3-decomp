#include "area040_13.h"

MATCH void func_801F2F80(void) {
    u16* request;
    s8*  mode;

    request  = &g_UIMessageRequest;
    *request = MESSAGE_NONE;
    if (MENU_SELECTION_IDLE()) {
        if (g_Game.members[0].chr.character_id != 2) {
            mode = &g_SceneEventState.mode;
            if (*mode == 0) {
                Game_SetScriptActive();
                *mode                  = 0x10;
                g_SceneEventState.step = 0;
            }
        } else {
            *request = 0x3C;
        }
    } else {
        g_GameFlags &= ~0x1006;
        g_SceneEventState.mode = 0;
        g_SceneEventState.step = 0;
    }
}
