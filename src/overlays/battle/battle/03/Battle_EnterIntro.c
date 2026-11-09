#include "battle_03.h"

/* func_801D1B94 */
MATCH void Battle_EnterIntro(void) {
    u8* value;
    u8  mode;
    u8* counter;

    /* Retail materialises &g_Battle.outcome.surprise once and reloads the group byte where the source reads it twice. */
    value = &g_BattleOutcome.surprise;
    if (((*value >= 2) || (D_8014837B == 1)) && ((func_801DE92C() & BYTE_MASK) == 0) && (EMI_IsReady() != 0)) {
        mode = 2;
        if (*value < 2) {
            mode = 1;
        }
        func_801D93E4(mode);
        func_801D9428(2);
        /* Retail keeps the mode byte's address in a register for the increment; a direct `+= 1` repeats lui. */
        counter                 = &g_Battle.phase.mode;
        g_Battle.phase.step     = 0;
        g_Battle.phase.sub_step = 0;
        *counter += 1;
    }
}
