#include "menu/gameui.h"

/* func_801F3C08, func_801F2FB4 */
MATCH void FairyCasino_AnswerPickNumbersInvite(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest = MSG_137;
    } else {
        g_MessageRequest = MSG_136;
        D_801F294C       = 2;
    }
}
