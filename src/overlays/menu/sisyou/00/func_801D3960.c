#include "sisyou_00.h"

/* Panel-lock flag owned by the main executable. */

MATCH void func_801D3960(void) {
    Message_StartAreaMessage((s16)(g_MenuMasterMessageIds[g_SceneEventSelection] + MASTER_MESSAGE_OFFER));
    g_GameStateIndex   = GAME_REQUEST_MESSAGE;
    g_MenuMasterCursor = 0;
    g_MenuMasterSubStep++;
}
