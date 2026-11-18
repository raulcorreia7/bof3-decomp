#include "area030_04.h"

/* Increments the panel animation counter, draws the current
 * sub-state cell through the later helper, and advances the panel state once
 * the counter reaches four. */
/* func_801DA508 */
MATCH void Fishing_CautionSlideOut(void) {
    FishingState* record;

    record             = FISHING_STATE;
    record->step_timer = (record->step_timer + 1);

    Fishing_DrawCautionBox((s16)(68 - FISHING_STATE->step_timer * 80), 78);

    if (FISHING_STATE->step_timer == 4) {
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 2));
        record            = FISHING_STATE;
        record->cue_index = 1;
        record            = FISHING_STATE;
        record->sub_index = 4;
    }

    Fishing_DrawDimScreen();
}
