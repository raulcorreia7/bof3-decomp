#include "sys/gameui.h"

/* func_801F3C08, func_801F2FB4 */
MATCH void FairyCasino_AnswerPickNumbersInvite(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest = 0x89;
    } else {
        g_MessageRequest = 0x88;
        D_801F294C       = 2;
    }
}
