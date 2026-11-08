#include "battle_03.h"

/* once the overlay loader is ready, starts the selection sound from the pending slot's kind byte and the
 * panel record, arms the panel state bytes and clears the scene stage counter.
 */
MATCH void func_801D39BC(void) {
    if (EMI_IsReady() != 0) {
        func_800AE108(g_BattleAction->unk_02, D_8014637C);
        g_BattleMode    = 3;
        g_BattleStep    = 2;
        g_BattleSubStep = 0;
        g_BattleUIStep  = 0;
    }
}
