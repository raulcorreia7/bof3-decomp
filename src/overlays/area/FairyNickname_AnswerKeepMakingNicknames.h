#include "sys/gameui.h"

/* func_801F3DDC, func_801F3188 */
MATCH void FairyNickname_AnswerKeepMakingNicknames(void) {
    if (MENU_SELECTION_IDLE()) {
        MESSAGE_REQUEST_CLEAR();
        D_801F294C = 0;
    } else {
        g_MessageRequest = FAIRY_MESSAGE_NICKNAME_GOODBYE;
        D_801F294C       = 4;
    }
}
