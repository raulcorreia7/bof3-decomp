#include "menu/gameui.h"

/* func_801F3AC8, func_801F2E74 */
MATCH void FairyCasino_AnswerGameChoice(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest            = MSG_111;
        g_SceneEventState.selection = 0;
    } else if (g_Zenny >= 500u) {
        g_MessageRequest            = MSG_125;
        g_SceneEventState.selection = 1;
    } else {
        g_MessageRequest                   = MSG_124;
        g_ScriptWorkRecord->callback_index = GAME_NONE;
    }
}
