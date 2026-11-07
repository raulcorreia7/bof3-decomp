#include "sys/gameui.h"

/* func_801F3AC8, func_801F2E74 */
MATCH void FairyCasino_AnswerGameChoice(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest      = FAIRY_MESSAGE_HIGH_LOW_RULES_KNOWN;
        g_SceneEventSelection = 0;
    } else if (g_Zenny >= 500u) {
        g_MessageRequest      = FAIRY_MESSAGE_NUMBERS_RULES_NEEDED;
        g_SceneEventSelection = 1;
    } else {
        g_MessageRequest                   = FAIRY_MESSAGE_CASINO_NOT_ENOUGH_ZENNY;
        g_ScriptWorkRecord->callback_index = GAME_NONE;
    }
}
