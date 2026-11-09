#include "area030_04.h"

/* Counts the AREA030 box timer down and, while it runs, draws the shrinking clip row for the selected entry. */
MATCH void func_801D41E4(void) {
    FishingState* work;
    FishingState* state;
    s32           index;

    work                = FISHING_STATE;
    work->step_timer_09 = (work->step_timer_09 - 1);

    state = FISHING_STATE;
    if (state->step_timer_09 != 0) {
        index = D_801E1E80[state->row_4B * 0xC] * 3;
        func_801D9740(D_801E1F16[index], D_801E1F14 + index, ((8 - (4 - state->step_timer_09) * 2) & 0xFE) | 0x80,
                      0x1D);
        return;
    }
    Actor_Clear();
}
