#include "sys/gameui.h"

/* func_801F3AC8, func_801F2E74 */
MATCH void FairyCasino_AnswerGameChoice(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest      = 0x6F;
        g_SceneEventSelection = 0;
    } else if (g_Zenny >= 500u) {
        g_MessageRequest      = 0x7D;
        g_SceneEventSelection = 1;
    } else {
        g_MessageRequest                   = 0x7C;
        g_ScriptWorkRecord->callback_index = 0xFF;
    }
}
