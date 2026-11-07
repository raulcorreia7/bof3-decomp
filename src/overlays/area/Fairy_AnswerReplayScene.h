#include "sys/gameui.h"

/* func_801F389C, func_801F2C48 */
MATCH void Fairy_AnswerReplayScene(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        g_ScriptVars[0]      = 0x28;
        g_SceneState.step_05 = 0x15;
    } else {
        g_ScriptVars[0]      = 0x32;
        g_SceneState.step_05 = 0x19;
    }
}
