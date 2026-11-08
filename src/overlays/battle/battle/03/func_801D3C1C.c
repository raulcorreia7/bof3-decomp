#include "battle_03.h"

/* once the overlay loader is ready, starts the selection sound from the pending slot's 16-bit value and the
 * panel record, arms the panel state bytes and clears the scene stage counter.
 */
MATCH void func_801D3C1C(void) {
    if (EMI_IsReady() != 0) {
        func_800AE260(g_Battle.action->unk_02, D_8014637C);
        g_Battle.phase.mode     = BATTLE_MODE_TURNS;
        g_Battle.phase.step     = 2;
        g_Battle.phase.sub_step = 0;
        g_Battle.ui_step        = 0;
    }
}
