#include "sys/gameui.h"

/* func_801F386C, func_801F2C18 */
MATCH void Fairy_AnswerWaitForNightfall(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_ARMED()) {
        g_SceneState.step_05 = 2;
    } else {
        g_SceneState.step_05 = 3;
    }
}
