#include "menu/gameui.h"

/* func_801F38E8, func_801F2C94 */
MATCH void FairyMusician_AnswerPlaySongs(void) {
    if (g_MessageChoice == 1) {
        g_MessageRequest                   = MSG_AREA175_THANKS_COME_BACK;
        g_ScriptWorkRecord->callback_index = GAME_NONE;
    } else {
        MESSAGE_REQUEST_CLEAR();
    }
}
