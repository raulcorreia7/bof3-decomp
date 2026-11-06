#include "sisyou_00.h"

/* Bit-array base owned by the main executable; only its address is taken. No
 * other consumer names the D_8014554C block (etc/game/00@0x801C2018 tests only its
 * bit 4). */

/* Panel-lock flag owned by the main executable. */

MATCH void func_801D26C4(void) {
    SYS_SetFlag(D_8014554C, g_SceneEventSelection);
    Message_StartAreaMessage(g_MasterMessageIds[g_SceneEventSelection]);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    g_MasterSubStep++;
}
