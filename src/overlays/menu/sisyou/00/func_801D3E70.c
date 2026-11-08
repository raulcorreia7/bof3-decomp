#include "sisyou_00.h"

/* Panel-lock flag owned by the main executable. */

MATCH void func_801D3E70(void) {
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        return;
    }
    g_MasterMenuCursor++;
    if ((g_MasterMenuCursor & BYTE_MASK) < g_Game.party_size) {
        g_MasterSubStep = 1;
    } else {
        g_MasterStep    = 2;
        g_MasterSubStep = 1;
    }
}
