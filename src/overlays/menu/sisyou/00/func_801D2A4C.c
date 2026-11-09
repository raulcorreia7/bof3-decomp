#include "sisyou_00.h"

/* Panel-lock flag owned by the main executable. */

/* Work-entry count and the two strided per-entry tables (0x140-byte work records, 0xA4-byte stock records). */

MATCH void func_801D2A4C(void) {
    s32 i;

    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        return;
    }
    for (i = 0; i < g_Game.party_size; i++) {
        if (g_Characters[g_Game.members[i].character_index].master_id == g_SceneEventSelection) {
            break;
        }
    }
    if (i < g_Game.party_size) {
        g_MenuMasterStep    = 4;
        g_MenuMasterSubStep = 0;
        return;
    }
    Message_StartAreaMessage((s16)(g_MenuMasterMessageIds[g_SceneEventSelection] + MASTER_MESSAGE_NO_PUPILS));
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    g_MenuMasterSubStep++;
}
