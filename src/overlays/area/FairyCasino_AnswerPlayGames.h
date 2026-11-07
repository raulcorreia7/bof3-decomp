#include "sys/gameui.h"

/* func_801F39EC, func_801F2D98 */
MATCH void FairyCasino_AnswerPlayGames(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest = 0x7A;
    } else {
        g_MessageRequest                   = 0x6E;
        g_ScriptWorkRecord->callback_index = 0xFF;
    }
}
