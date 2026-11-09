#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Walks the AREA030 prompt cue table. */
MATCH void func_801D5958(void) {
    FishingState* work;
    FishingState* next;
    FishingState* cur;
    s32           index;

    work = FISHING_STATE;
    if (work->step_timer_09 == 0) {
        index = work->step_index_0A * 2;
        if (D_801E1FE8[index] == GAME_NONE) {
            work->step_index_0A = D_801E1FE9[index];
        }

        next = FISHING_STATE;
        Actor_SelectScript(D_801E1FE8[next->step_index_0A * 2]);

        cur                = FISHING_STATE;
        cur->step_timer_09 = D_801E1FE9[cur->step_index_0A * 2];

        cur                = FISHING_STATE;
        cur->step_index_0A = (cur->step_index_0A + 1);
    } else {
        work->step_timer_09 = (work->step_timer_09 - 1);
        Actor_StepAnimLoop();
    }
    Area_AddActor();
}
