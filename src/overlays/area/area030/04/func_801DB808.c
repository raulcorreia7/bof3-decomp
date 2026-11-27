#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callees. */

/* Counts the AREA030 prompt timer down while the slot row scrolls,
 * then steps the work state once the timer expires and runs the shared tails. */
MATCH void func_801DB808(void) {
    s32 offset;

    SELF(FishingState)->timer = (SELF(FishingState)->timer - 1);

    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, g_Actors[g_FishingHookedFish].unk_06);

    offset = g_FishingHookedFish * 0x98;
    Fishing_DrawCatchRow(g_Actors[g_FishingHookedFish].unk_06, 0, SELF(FishingState)->timer);

    if (SELF(FishingState)->timer == 0) {
        SELF(FishingState)->sub_index = (SELF(FishingState)->sub_index + 1);
    }
    Script_AnimStepLoop();
    Fishing_DrawDimScreen();
}
