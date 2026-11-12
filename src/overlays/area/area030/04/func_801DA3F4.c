#include "area030_04.h"

/* Decrements the panel animation counter, draws the current
 * sub-state cell through the later helper, and advances the panel state once
 * the counter reaches zero. */
MATCH void func_801DA3F4(void) {
    FishingState* record;

    record                = FISHING_STATE;
    record->step_timer_09 = (record->step_timer_09 - 1);

    Fishing_DrawCautionBox((s16)(FISHING_STATE->step_timer_09 * 80 + 68), 78);

    record = FISHING_STATE;
    if (record->step_timer_09 == 0) {
        record->cue_index_06 = 1;
        record               = FISHING_STATE;
        record->sub_index_03 = (record->sub_index_03 + 1);
    }

    Fishing_DrawDimScreen();
}
