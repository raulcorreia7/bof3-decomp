#include "sisyou_00.h"

/* Panel-lock flag owned by the main executable. */

MATCH void func_801D3960(void) {
    Message_StartAreaMessage((s16)(g_MasterMessageIds[g_SceneEventSelection] + 5));
    g_GameStateIndex   = GAME_REQUEST_MESSAGE;
    g_MasterMenuCursor = 0;
    g_MasterSubStep++;
}
