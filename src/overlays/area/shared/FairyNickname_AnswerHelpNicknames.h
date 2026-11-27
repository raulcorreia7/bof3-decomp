#include "menu/gameui.h"

/* func_801F3D18, func_801F30C4 */
MATCH void FairyNickname_AnswerHelpNicknames(void) {
    if (MENU_SELECTION_IDLE()) {
        MESSAGE_REQUEST_CLEAR();
    } else {
        g_UIMessageRequest                 = MSG_AREA175_BYE_SEE_YOU;
        g_ScriptWorkRecord->callback_index = GAME_NONE;
    }
}
