#include "sys/gameui.h"

/* func_801F3D18, func_801F30C4 */
MATCH void FairyNickname_AnswerHelpNicknames(void) {
    if (MENU_SELECTION_IDLE()) {
        MESSAGE_REQUEST_CLEAR();
    } else {
        g_MessageRequest                   = FAIRY_MESSAGE_NICKNAME_GOODBYE;
        g_ScriptWorkRecord->callback_index = 0xFF;
    }
}
