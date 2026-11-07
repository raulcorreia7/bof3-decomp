#include "sys/gameui.h"

/* func_801F38E8, func_801F2C94 */
MATCH void FairyMusician_AnswerPlaySongs(void) {
    if (g_MessageChoice == 1) {
        g_MessageRequest                   = FAIRY_MESSAGE_MUSICIAN_THANKS;
        g_ScriptWorkRecord->callback_index = GAME_NONE;
    } else {
        MESSAGE_REQUEST_CLEAR();
    }
}
