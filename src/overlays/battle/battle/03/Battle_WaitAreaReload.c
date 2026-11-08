#include "battle_03.h"

/* func_801D716C */
MATCH void Battle_WaitAreaReload(void) {
    if (EMI_IsReady() != 0) {
        g_Battle.phase.step     = 4;
        g_Battle.phase.sub_step = 0;
    }
}
