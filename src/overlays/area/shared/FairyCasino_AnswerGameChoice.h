#include "menu/gameui.h"

/* func_801F3AC8, func_801F2E74 */
MATCH void FairyCasino_AnswerGameChoice(void) {
    if (MENU_SELECTION_IDLE()) {
        g_UIMessageRequest          = MSG_AREA175_ASK_RULES_KNOWN;
        g_SceneEventState.selection = 0;
    } else if (g_Zenny >= 500u) {
        g_UIMessageRequest          = MSG_AREA175_ASK_NEED_RULES;
        g_SceneEventState.selection = 1;
    } else {
        g_UIMessageRequest                 = MSG_AREA175_NOT_ENOUGH_ZENNY;
        g_ScriptWorkRecord->callback_index = GAME_NONE;
    }
}
