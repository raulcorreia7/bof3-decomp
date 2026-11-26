#include "area030_04.h"

/* Counts the AREA030 box timer down and, while it runs, draws the
 * shrinking clip row for the selected entry; at zero it hands off to the box
 * teardown. */
MATCH void func_801D41E4(void) {
    FishingState* work;
    FishingState* state;
    s32           index;

    work        = SELF(FishingState);
    work->timer = (work->timer - 1);

    state = SELF(FishingState);
    if (state->timer != 0) {
        index = D_801E1E80[state->row_4B * 0xC] * 3;
        func_801D9740(D_801E1F16[index], D_801E1F14 + index, ((8 - (4 - state->timer) * 2) & 0xFE) | 0x80, 0x1D);
        return;
    }
    Actor_Clear();
}
