#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Scrolls the AREA030 prompt rows down with the timer and advances
 * the panel step once the timer expires. */
MATCH void func_801DBA94(void) {
    FishingState* work;
    FishingState* state;
    s32           offset;

    work                = FISHING_STATE;
    work->step_timer_09 = (work->step_timer_09 - 1);

    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, D_8014688E[g_FishingHookedFish * 0x98]);

    offset = g_FishingHookedFish * 0x98;
    func_801E1004(D_8014688E[offset], D_80146918[offset], 0);
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_STATE->step_timer_09 * FISHING_CATCH_ROW_STEP + FISHING_CATCH_RANK_Y);
    func_801E1C7C();

    state = FISHING_STATE;
    if (state->step_timer_09 == 0) {
        state->sub_index_03 = (state->sub_index_03 + 1);
    }
    Actor_StepAnimLoop();
    Fishing_DrawDimScreen();
}
