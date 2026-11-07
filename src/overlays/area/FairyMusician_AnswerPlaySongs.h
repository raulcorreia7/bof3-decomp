#include "sys/gameui.h"

/* func_801F38E8, func_801F2C94 */
MATCH void FairyMusician_AnswerPlaySongs(void) {
    if (g_MessageChoice == 1) {
        g_MessageRequest                   = 0x5A;
        g_ScriptWorkRecord->callback_index = 0xFF;
    } else {
        MESSAGE_REQUEST_CLEAR();
    }
}
