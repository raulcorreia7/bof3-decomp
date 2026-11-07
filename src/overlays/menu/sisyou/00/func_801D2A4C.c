#include "sisyou_00.h"

/* Panel-lock flag owned by the main executable. */

/* Work-entry count and the two strided per-entry tables (0x140-byte work
 * records, 0xA4-byte stock records); the 2-D form keeps the original's
 * symbol+index addressing. */

MATCH void func_801D2A4C(void) {
    s32 i;

    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        return;
    }
    for (i = 0; i < g_PartySize; i++) {
        if (g_Characters[g_BattlePartyBattlers[i].character_index].master_id == g_SceneEventSelection) {
            break;
        }
    }
    if (i < g_PartySize) {
        g_MasterStep    = 4;
        g_MasterSubStep = 0;
        return;
    }
    Message_StartAreaMessage((s16)(g_MasterMessageIds[g_SceneEventSelection] + MASTER_MESSAGE_NO_PUPILS));
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    g_MasterSubStep++;
}
