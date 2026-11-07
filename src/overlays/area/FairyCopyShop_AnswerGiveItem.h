#include "sys/gameui.h"

/* func_801F392C, func_801F2CD8 */
MATCH void FairyCopyShop_AnswerGiveItem(void) {
    if (g_MessageChoice == 1) {
        g_MessageRequest = FAIRY_MESSAGE_COPY_SHOP_DECLINED;
        g_SceneEventStep = 1;
    } else {
        MESSAGE_REQUEST_CLEAR();
    }
}
