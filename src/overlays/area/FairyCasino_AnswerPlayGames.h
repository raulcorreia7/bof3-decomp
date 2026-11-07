#include "sys/gameui.h"

/* func_801F39EC, func_801F2D98 */
MATCH void FairyCasino_AnswerPlayGames(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest = FAIRY_MESSAGE_CASINO_CHOOSE_GAME;
    } else {
        g_MessageRequest                   = FAIRY_MESSAGE_CASINO_NOT_PLAYING;
        g_ScriptWorkRecord->callback_index = 0xFF;
    }
}
