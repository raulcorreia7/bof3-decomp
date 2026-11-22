#include "area030_04.h"

/* Ticks the panel animation counter down, redraws the two panel
 * rows, and advances the panel state once the counter reaches zero. */
MATCH void func_801DB738(void) {
    FishingState* record;

    record             = TASK(FishingState);
    record->step_timer = (record->step_timer - 1);
    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);

    Fishing_DrawCatchIcon((TASK(FishingState)->step_timer * FISHING_CATCH_ICON_STEP) + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, g_Actors[g_FishingHookedFish].unk_06);

    record = TASK(FishingState);
    if (record->step_timer == 0) {
        record->step_timer = 4;
        record             = TASK(FishingState);
        record->sub_index  = (record->sub_index + 1);
    }

    Script_AnimStepLoop();
    Fishing_DrawDimScreen();
}
