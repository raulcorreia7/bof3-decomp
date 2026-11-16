#include "menu/gameui.h"

/* func_801F3BA4, func_801F2F50 */
MATCH void FairyCasino_AnswerNumbersPlayAgain(void) {
    u16 value;

    if (MENU_SELECTION_ARMED()) {
        value = MSG_123;
    } else if (g_Zenny < 500u) {
        value = MSG_124;
    } else {
        g_MessageRequest = MSG_127;
        D_801F294F       = 0;
        return;
    }
    g_MessageRequest = value;
    D_801F294F       = 1;
}
