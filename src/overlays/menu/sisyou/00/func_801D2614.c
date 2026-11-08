#include "sisyou_00.h"

/* Panel-lock flag owned by the main executable. */

MATCH void func_801D2614(void) {
    s32 step;

    if (SYS_TestFlag(D_8014554F, g_SceneEventSelection) != 0) {
        step = 5;
    } else if (g_SceneEventSelection == MASTER_DEIS) {
        Message_StartAreaMessage(MASTER_MESSAGE_DEIS_UNAVAILABLE);
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        step             = 6;
    } else {
        step = 1;
    }
    g_MenuMasterStep = step;
}
