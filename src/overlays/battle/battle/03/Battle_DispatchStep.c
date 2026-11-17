#include "battle_03.h"

/* func_801D11D8 */
MATCH void Battle_DispatchStep(void) {
    Callback handlers[2] = {Battle_Reset, Battle_DispatchEntrance};

    handlers[g_Battle.phase.step]();
}
