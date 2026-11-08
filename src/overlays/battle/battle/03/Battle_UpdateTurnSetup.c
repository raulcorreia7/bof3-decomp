#include "battle_03.h"

/* func_801D2740 */
MATCH void Battle_UpdateTurnSetup(void) {
    D_801EAC04[g_Battle.phase.step]();
}
