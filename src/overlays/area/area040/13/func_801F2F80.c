#include "area040_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2F80(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        if (g_Game.members[0].chr.character_id == 2) {
            g_MessageRequest = 0x3C;
        } else if (g_SceneEventState.mode == 0) {
            Game_SetScriptActive();
            g_SceneEventState.mode = 0x10;
            g_SceneEventState.step = 0;
        }
    } else {
        g_SceneEventState.mode = 0;
        g_SceneEventState.step = 0;
        g_GameFlags &= ~0x1006;
    }
}
#else
INCLUDE_ASM(func_801F2F80);
#endif
