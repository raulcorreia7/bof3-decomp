#include "sisyou_00.h"

/* func_801D2B64 */
MATCH void Master_StartFarewell(void) {
    u8* state = &g_GameStateIndex;

    if (*state == 2) {
        return;
    }
    Message_StartAreaMessage((s16)(g_MenuMasterMessageIds[g_SceneEventSelection] + MASTER_MESSAGE_FAREWELL));
    *state              = 2;
    g_MenuMasterStep    = 6;
    g_MenuMasterSubStep = 0;
}
