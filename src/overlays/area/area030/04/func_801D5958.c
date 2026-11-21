#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Walks the AREA030 prompt cue table: while a cue is pending it
 * decrements the countdown and runs the per-frame tail; otherwise it advances
 * the cue index, arms the cue through the mode helper, latches the new
 * countdown and bumps the index. */
MATCH void func_801D5958(void) {
    FishingState* work;
    FishingState* next;
    FishingState* cur;
    s32           index;

    work = FISHING_STATE;
    if (work->step_timer == 0) {
        index = work->step_index * 2;
        if (D_801E1FE8[index] == GAME_NONE) {
            work->step_index = D_801E1FE9[index];
        }

        next = FISHING_STATE;
        Script_Select(D_801E1FE8[next->step_index * 2]);

        cur             = FISHING_STATE;
        cur->step_timer = D_801E1FE9[cur->step_index * 2];

        cur             = FISHING_STATE;
        cur->step_index = (cur->step_index + 1);
    } else {
        work->step_timer = (work->step_timer - 1);
        Actor_StepAnimLoop();
    }
    Area_AddActor();
}
