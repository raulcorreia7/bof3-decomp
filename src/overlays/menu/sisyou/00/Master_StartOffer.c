#include "sisyou_00.h"

/* Panel-lock flag owned by the main executable. */

MATCH void Master_StartOffer(void) {
    MESSAGE_START_WAIT((s16)(g_MenuMasterMessageIds[g_SceneEventState.selection] + MASTER_MESSAGE_OFFER));
    g_MenuMasterSubStep++;
}
