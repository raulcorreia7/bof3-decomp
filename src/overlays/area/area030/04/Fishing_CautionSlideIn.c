#include "area030_04.h"

/* Decrements the panel animation counter, draws the current
 * sub-state cell through the later helper, and advances the panel state once
 * the counter reaches zero. */
/* func_801DA3F4 */
MATCH void Fishing_CautionSlideIn(void) {
    FishingState* record;

    record             = FISHING_STATE;
    record->step_timer = (record->step_timer - 1);

    Fishing_DrawCautionBox((s16)(FISHING_STATE->step_timer * 80 + 68), 78);

    record = FISHING_STATE;
    if (record->step_timer == 0) {
        record->cue_index = 1;
        record            = FISHING_STATE;
        record->sub_index = (record->sub_index + 1);
    }

    Fishing_DrawDimScreen();
}
