#include "sisyou_00.h"

/* Panel-lock flag owned by the main executable. */

MATCH void Master_StartOffer(void) {
    Message_StartAreaMessage((s16)(g_MenuMasterMessageIds[g_SceneEventSelection] + MASTER_MESSAGE_OFFER));
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    g_MenuMasterSubStep++;
}
