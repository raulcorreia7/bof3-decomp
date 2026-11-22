#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Scrolls the AREA030 prompt rows down with the timer and advances
 * the panel step once the timer expires. */
MATCH void func_801DBA94(void) {
    FishingState* work;
    FishingState* state;
    s32           offset;

    work             = FISHING_STATE;
    work->step_timer = (work->step_timer - 1);

    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, D_8014688E[g_FishingHookedFish * 0x98]);

    offset = g_FishingHookedFish * 0x98;
    Fishing_DrawCatchRow(D_8014688E[offset], D_80146918[offset], 0);
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_STATE->step_timer * FISHING_CATCH_ROW_STEP + FISHING_CATCH_RANK_Y);
    func_801E1C7C();

    state = FISHING_STATE;
    if (state->step_timer == 0) {
        state->sub_index = (state->sub_index + 1);
    }
    Script_AnimStepLoop();
    Fishing_DrawDimScreen();
}
