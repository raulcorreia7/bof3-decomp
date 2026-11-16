#include "menu/gameui.h"

/* func_801F39EC, func_801F2D98 */
MATCH void FairyCasino_AnswerPlayGames(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest = MSG_122;
    } else {
        g_MessageRequest                   = MSG_110;
        g_ScriptWorkRecord->callback_index = GAME_NONE;
    }
}
