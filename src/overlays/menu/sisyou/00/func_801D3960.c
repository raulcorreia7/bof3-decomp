#include "sisyou_00.h"

/* Panel-lock flag owned by the main executable. */

MATCH void func_801D3960(void) {
    MESSAGE_START_WAIT((s16)(g_MenuMasterMessageIds[g_SceneEventState.selection] + MASTER_MESSAGE_OFFER));
    g_MenuMasterCursor = 0;
    g_MenuMasterSubStep++;
}
