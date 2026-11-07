#include "sys/gameui.h"

/* func_801F3998, func_801F2D44 */
MATCH void FairyCopyShop_AnswerChooseOther(void) {
    if (MENU_SELECTION_IDLE()) {
        MESSAGE_REQUEST_CLEAR();
        D_801F294D = 0;
    } else {
        g_MessageRequest = FAIRY_MESSAGE_COPY_SHOP_DECLINED;
        D_801F294C++;
    }
}
