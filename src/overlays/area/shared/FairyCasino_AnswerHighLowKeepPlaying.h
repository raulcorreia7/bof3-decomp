#include "menu/gameui.h"

/* func_801F3A84, func_801F2E30 */
MATCH void FairyCasino_AnswerHighLowKeepPlaying(void) {
    if (MENU_SELECTION_IDLE()) {
        MESSAGE_REQUEST_CLEAR();
    } else {
        g_UIMessageRequest = MSG_AREA175_HIGH_LOW_QUIT_PAYOUT;
        D_801F294D         = 0xA;
    }
}
