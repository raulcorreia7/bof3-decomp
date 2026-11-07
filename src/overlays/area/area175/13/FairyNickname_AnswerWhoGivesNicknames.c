#include "area175_13.h"

/* func_801F3D60 */
MATCH void FairyNickname_AnswerWhoGivesNicknames(void) {
    if (MENU_SELECTION_ARMED()) {
        D_801F294C = 2;
    } else {
        D_801F294C = 1;
    }
    g_MessageRequest = FAIRY_MESSAGE_NICKNAME_PICK_FAIRY;
}
