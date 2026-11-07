#include "sys/gameui.h"

/* func_801F3C08, func_801F2FB4 */
MATCH void FairyCasino_AnswerPickNumbersInvite(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest = FAIRY_MESSAGE_PICK_NUMBERS_RULES_REMEMBERED;
    } else {
        g_MessageRequest = FAIRY_MESSAGE_PICK_NUMBERS_DECLINED;
        D_801F294C       = 2;
    }
}
