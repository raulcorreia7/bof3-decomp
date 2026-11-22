#include "area030_04.h"

/* Increments the panel animation counter, draws the current
 * sub-state cell through the later helper, and advances the panel state once
 * the counter reaches four. */
/* func_801DA508 */
MATCH void Fishing_CautionSlideOut(void) {
    FishingState* record;

    record        = TASK(FishingState);
    record->timer = (record->timer + 1);

    Fishing_DrawCautionBox((s16)(68 - TASK(FishingState)->timer * 80), 78);

    if (TASK(FishingState)->timer == 4) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        record            = TASK(FishingState);
        record->cue_index = 1;
        record            = TASK(FishingState);
        record->sub_index = 4;
    }

    Fishing_DrawDimScreen();
}
