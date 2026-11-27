#include "menu/gameui.h"

/* func_801F39EC, func_801F2D98 */
MATCH void FairyCasino_AnswerPlayGames(void) {
    if (MENU_SELECTION_IDLE()) {
        g_UIMessageRequest = MSG_AREA175_ASK_WHICH_GAME;
    } else {
        g_UIMessageRequest                 = MSG_AREA175_DECLINE_GAME;
        g_ScriptWorkRecord->callback_index = GAME_NONE;
    }
}
