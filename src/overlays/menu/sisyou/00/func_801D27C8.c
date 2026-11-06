#include "sisyou_00.h"

/* Panel-lock flag owned by the main executable. */

MATCH void func_801D27C8(void) {
    Message_StartAreaMessage((s16)(g_MasterMessageIds[g_SaveData.scene_event.selection] + 5));
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    g_MasterSubStep++;
}
