#include "sys/gameui.h"

/* func_801F3EB4, func_801F3260 */
MATCH void FairySinger_AnswerHearSong(void) {
    if (MENU_SELECTION_IDLE()) {
        MESSAGE_REQUEST_CLEAR();
        D_801F2944 = 0;
    } else if (g_MessageChoice == 1) {
        MESSAGE_REQUEST_CLEAR();
        D_801F2944 = 1;
    } else {
        g_MessageRequest                   = 0x2A1;
        g_ScriptWorkRecord->callback_index = 0xFF;
    }
}
