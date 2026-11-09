#include "battle_03.h"

/* func_801D1AB4 */
MATCH void Battle_WaitForUI(void) {
    u8* counter;

    if (D_80148357 == 1) {
        /* Retail materialises &g_Battle.phase.sub_step once and reads and writes the sub-step byte through it. */
        counter = &g_Battle.phase.sub_step;
        *counter += 1;
    }
}
