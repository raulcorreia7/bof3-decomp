#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callees. */

/* Counts the AREA030 prompt timer down while the slot row scrolls,
 * then steps the work state once the timer expires and runs the shared tails. */
MATCH void func_801DB808(void) {
    s32 offset;

    FISHING_STATE->step_timer = (FISHING_STATE->step_timer - 1);

    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, D_8014688E[g_FishingHookedFish * 0x98]);

    offset = g_FishingHookedFish * 0x98;
    Fishing_DrawCatchRow(D_8014688E[offset], 0, FISHING_STATE->step_timer);

    if (FISHING_STATE->step_timer == 0) {
        FISHING_STATE->sub_index = (FISHING_STATE->sub_index + 1);
    }
    Actor_StepAnimLoop();
    Fishing_DrawDimScreen();
}
