#include "menu/gameui.h"

/* func_801F3EB4, func_801F3260 */
MATCH void FairySinger_AnswerHearSong(void) {
    if (MENU_SELECTION_IDLE()) {
        MESSAGE_REQUEST_CLEAR();
        D_801F2944 = 0;
    } else if (g_UIMessageChoice == 1) {
        MESSAGE_REQUEST_CLEAR();
        D_801F2944 = 1;
    } else {
        g_UIMessageRequest                 = MSG_AREA175_SEE_YOU_LATER_END;
        g_ScriptWorkRecord->callback_index = GAME_NONE;
    }
}
