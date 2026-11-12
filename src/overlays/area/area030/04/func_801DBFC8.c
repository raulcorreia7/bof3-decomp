#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Draws the AREA030 prompt rows for the current slot, arms the cursor
 * and caption rows and, on any pad input, retires the caret and advances the
 * panel step. */
MATCH void func_801DBFC8(void) {
    FishingState* work;
    s32           offset;

    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, D_8014688E[g_FishingHookedFish * 0x98]);

    offset = g_FishingHookedFish * 0x98;
    func_801E1004(D_8014688E[offset], D_80146918[offset], 0);
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_CATCH_RANK_Y);
    Fishing_DrawIconRow(8, FISHING_CATCH_ROW_Y, 67);

    if (g_InputPressed != 0) {
        FISHING_STATE->cue_index_06 = 0;
        work                        = FISHING_STATE;
        work->sub_index_03          = (work->sub_index_03 + 1);
    }
    Actor_StepAnimLoop();
    Fishing_DrawDimScreen();
}
