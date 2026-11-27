#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Draws the AREA030 prompt rows for the current slot, arms the cursor
 * and caption rows and, on any pad input, retires the caret and advances the
 * panel step. */
MATCH void func_801DBFC8(void) {
    FishingState* work;
    s32           offset;

    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, g_Actors[g_FishingHookedFish].unk_06);

    offset = g_FishingHookedFish * 0x98;
    Fishing_DrawCatchRow(g_Actors[g_FishingHookedFish].unk_06, D_80146918[offset], 0);
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_CATCH_RANK_Y);
    Fishing_DrawIconRow(8, FISHING_CATCH_ROW_Y, 67);

    if (g_PadStates[0].pressed != 0) {
        SELF(FishingState)->cue_index = 0;
        work                          = SELF(FishingState);
        work->sub_index               = (work->sub_index + 1);
    }
    Script_AnimStepLoop();
    Fishing_DrawDimScreen();
}
