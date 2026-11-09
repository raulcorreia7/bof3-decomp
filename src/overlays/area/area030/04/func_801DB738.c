#include "area030_04.h"

/* Ticks the panel animation counter down, redraws the two panel
 * rows, and advances the panel state once the counter reaches zero. */
MATCH void func_801DB738(void) {
    FishingState* record;

    record                = FISHING_STATE;
    record->step_timer_09 = (record->step_timer_09 - 1);
    func_801E0ED0(0, FISHING_CATCH_BAR_Y);

    func_801E0F4C((FISHING_STATE->step_timer_09 * FISHING_CATCH_ICON_STEP) + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, g_Actors[g_FishingHookedFish].unk_06);

    record = FISHING_STATE;
    if (record->step_timer_09 == 0) {
        record->step_timer_09 = 4;
        record                = FISHING_STATE;
        record->sub_index_03  = (record->sub_index_03 + 1);
    }

    Actor_StepAnimLoop();
    func_801E16DC();
}
