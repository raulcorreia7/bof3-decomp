#include "menu/gameui.h"

/* func_801F3C08, func_801F2FB4 */
MATCH void FairyCasino_AnswerPickNumbersInvite(void) {
    if (MENU_SELECTION_IDLE()) {
        g_UIMessageRequest = MSG_AREA175_ASK_RULES_REMEMBERED;
    } else {
        g_UIMessageRequest = MSG_AREA175_DECLINE_PICK_NUMBERS;
        D_801F294C         = 2;
    }
}
