#include "menu/gameui.h"

/* func_801F392C, func_801F2CD8 */
MATCH void FairyCopyShop_AnswerGiveItem(void) {
    if (g_UiMessageChoice == 1) {
        g_UiMessageRequest     = MSG_AREA175_SEE_YOU_LATER;
        g_SceneEventState.step = 1;
    } else {
        MESSAGE_REQUEST_CLEAR();
    }
}
