#include "sisyou_00.h"

/* Panel-lock flag owned by the main executable. */

MATCH void func_801D2738(void) {
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        return;
    }
    SYS_SetFlag(D_8014554F, g_SceneEventSelection);
    g_MenuMasterStep    = 3;
    g_MenuMasterSubStep = 0;
}
