#include "sisyou_00.h"

/* Bit-array base owned by the main executable; only its address is taken. No
 * other consumer names the D_8014554C block (etc/game/00@0x801C2018 tests only its
 * bit 4). */

/* Panel-lock flag owned by the main executable. */

/* FAKE: retail materializes the byte address at each read; the record member reuses one. */
MATCH void func_801D26C4(void) {
    SYS_SetFlag(D_8014554C, g_SceneEventSelection);
    MESSAGE_START_WAIT(g_MenuMasterMessageIds[g_SceneEventSelection]);
    g_MenuMasterSubStep++;
}
