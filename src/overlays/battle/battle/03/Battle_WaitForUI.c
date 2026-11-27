#include "battle_03.h"

/* func_801D1AB4 */
MATCH void Battle_WaitForUI(void) {
    u8* counter;

    if (g_UIPanelTasks[1].state == 1) {
        /* Retail materialises &g_Battle.phase.sub_step once and reads and writes the
         * sub-step byte through it; a direct `+= 1` repeats lui. */
        counter = &g_Battle.phase.sub_step;
        *counter += 1;
    }
}
