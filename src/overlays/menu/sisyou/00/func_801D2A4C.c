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
        if (g_SaveData.characters[D_80145FCC.rows[i][0]].master_id == D_801448ED) {
            break;
        }
    }
    if (i < g_PartySize) {
        g_MasterStep    = 4;
        g_MasterSubStep = 0;
        return;
    }
    Message_StartAreaMessage((s16)(g_MasterMessageIds[D_801448ED] + 9));
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    g_MasterSubStep++;
}
