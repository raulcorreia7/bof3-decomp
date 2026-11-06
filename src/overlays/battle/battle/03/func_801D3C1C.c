#include "battle_03.h"

/* once the overlay loader is ready, starts the selection sound from the pending slot's 16-bit value and the
 * panel record, arms the panel state bytes and clears the scene stage counter.
 */
MATCH void func_801D3C1C(void) {
    if (EMI_LoaderIsReady() != 0) {
        func_800AE260(g_BattleAction->unk_02, D_8014637C);
        g_BattleMode    = 3;
        g_BattleStep    = 2;
        g_BattleSubStep = 0;
        g_BattleUIStep  = 0;
    }
}
