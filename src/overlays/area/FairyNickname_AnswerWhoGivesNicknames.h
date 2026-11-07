#include "sys/gameui.h"

/* func_801F3D60, func_801F310C */
MATCH void FairyNickname_AnswerWhoGivesNicknames(void) {
    if (MENU_SELECTION_IDLE()) {
        D_801F294C = 1;
    } else {
        D_801F294C = 2;
    }
    g_MessageRequest = 0xEF;
}
