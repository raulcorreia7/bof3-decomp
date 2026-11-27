#include "menu/gameui.h"

/* func_801F3CCC, func_801F3078 */
MATCH void FairyCasino_AnswerHighLowPlayAgain(void) {
    if (MENU_SELECTION_IDLE()) {
        g_UIMessageRequest = MSG_AREA175_HIGH_LOW_START;
        D_801F294D         = 0xB;
    } else {
        g_UIMessageRequest = MSG_AREA175_DECLINE_HIGH_LOW;
        D_801F294D         = 0xC;
    }
    D_801F294E = 0;
}
