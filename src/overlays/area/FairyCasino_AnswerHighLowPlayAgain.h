#include "sys/gameui.h"

/* func_801F3CCC, func_801F3078 */
MATCH void FairyCasino_AnswerHighLowPlayAgain(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest = 0x78;
        D_801F294D       = 0xB;
    } else {
        g_MessageRequest = 0x72;
        D_801F294D       = 0xC;
    }
    D_801F294E = 0;
}
