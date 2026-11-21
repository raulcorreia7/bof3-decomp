#include "sisyou_00.h"

/* func_801D2B64 */
MATCH void Master_StartFarewell(void) {
    u8* state = &g_GameStateIndex;

    if (*state == GAME_REQUEST_MESSAGE) {
        return;
    }
    UI_MessageStartArea((s16)(g_MenuMasterMessageIds[g_SceneEventState.selection] + MASTER_MESSAGE_FAREWELL));
    *state              = GAME_REQUEST_MESSAGE;
    g_MenuMasterStep    = 6;
    g_MenuMasterSubStep = 0;
}
