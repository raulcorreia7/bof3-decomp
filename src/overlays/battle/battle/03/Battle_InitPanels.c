#include "battle_03.h"

/* func_801D1AE8 */
MATCH void Battle_InitPanels(void) {
    s32 i;
    s32 index;
    u8* counter;

    func_801D9388(0);
    i = 0;
    if (g_Battle.outcome.surprise >= 2u) {
        D_8014837B = 2u;
        do {
            index                        = i & BYTE_MASK;
            g_Battle.panel_widths[index] = 0;
            i += 1;
        } while ((i & BYTE_MASK) < 7u);
    } else {
        do {
            index                        = i & BYTE_MASK;
            g_Battle.panel_widths[index] = 0x10;
            i += 1;
        } while ((i & BYTE_MASK) < 7u);
    }
    /* Retail keeps the sub-step byte's address in a register for the increment; a direct `+= 1` repeats lui. */
    counter = &g_Battle.phase.sub_step;
    *counter += 1;
}
