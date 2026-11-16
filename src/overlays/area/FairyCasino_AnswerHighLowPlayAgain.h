#include "menu/gameui.h"

/* func_801F3CCC, func_801F3078 */
MATCH void FairyCasino_AnswerHighLowPlayAgain(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest = MSG_120;
        D_801F294D       = 0xB;
    } else {
        g_MessageRequest = MSG_114;
        D_801F294D       = 0xC;
    }
    D_801F294E = 0;
}
