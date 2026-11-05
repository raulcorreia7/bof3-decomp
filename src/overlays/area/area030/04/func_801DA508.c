#include "area030_04.h"

/* Increments the panel animation counter, draws the current
 * sub-state cell through the later helper, and advances the panel state once
 * the counter reaches four. */
MATCH void func_801DA508(void) {
    FishingState* record;

    record                = FISHING_STATE;
    record->step_timer_09 = (record->step_timer_09 + 1);

    func_801E19CC((s16)(0x44 - FISHING_STATE->step_timer_09 * 80), 0x4E);

    if (FISHING_STATE->step_timer_09 == 4) {
        SND_PlayCue(EMI_CUE_ID(1, 2));
        record               = FISHING_STATE;
        record->cue_index_06 = 1;
        record               = FISHING_STATE;
        record->sub_index_03 = 4;
    }

    func_801E16DC();
}
