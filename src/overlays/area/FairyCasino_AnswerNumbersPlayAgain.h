#include "sys/gameui.h"

/* func_801F3BA4, func_801F2F50 */
MATCH void FairyCasino_AnswerNumbersPlayAgain(void) {
    u16 value;

    if (MENU_SELECTION_ARMED()) {
        value = FAIRY_MESSAGE_NUMBERS_DECLINED;
    } else if (g_Zenny < 500u) {
        value = FAIRY_MESSAGE_CASINO_NOT_ENOUGH_ZENNY;
    } else {
        g_MessageRequest = FAIRY_MESSAGE_NUMBERS_START;
        D_801F294F       = 0;
        return;
    }
    g_MessageRequest = value;
    D_801F294F       = 1;
}
