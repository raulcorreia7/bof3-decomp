#include "menu/gameui.h"

/* func_801F3BA4, func_801F2F50 */
MATCH void FairyCasino_AnswerNumbersPlayAgain(void) {
    u16 value;

    if (MENU_SELECTION_ARMED()) {
        value = MSG_AREA175_DECLINE_NUMBERS;
    } else if (g_Zenny < 500u) {
        value = MSG_AREA175_NOT_ENOUGH_ZENNY;
    } else {
        g_UIMessageRequest = MSG_AREA175_NUMBERS_START;
        D_801F294F         = 0;
        return;
    }
    g_UIMessageRequest = value;
    D_801F294F         = 1;
}
