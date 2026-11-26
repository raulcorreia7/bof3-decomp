#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Draws the AREA030 prompt rows for the current slot and, at the end
 * of the fade, retires or advances the sub-state selected by the work byte. */
MATCH void func_801DBD6C(void) {
    FishingState* work;
    s32           offset;
    u16           cue;
    u8            state;

    work        = SELF(FishingState);
    work->timer = (work->timer - 1);

    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, g_Actors[g_FishingHookedFish].unk_06);

    offset = g_FishingHookedFish * 0x98;
    Fishing_DrawCatchRow(g_Actors[g_FishingHookedFish].unk_06, D_80146918[offset], 0);
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_CATCH_RANK_Y);

    work  = SELF(FishingState);
    state = work->saved_index;
    if (state == 1) {
        cue = 0x43;
        Fishing_DrawIconRow(8, work->timer * FISHING_CATCH_ROW_STEP + FISHING_CATCH_ROW_Y, cue);
    } else if (state == 2) {
        cue = 0x42;
        Fishing_DrawIconRow(8, work->timer * FISHING_CATCH_ROW_STEP + FISHING_CATCH_ROW_Y, cue);
    }

    work = SELF(FishingState);
    if (work->timer == 0) {
        state = work->saved_index;
        if (state == 1) {
            work->cue_index = 0;
            work            = SELF(FishingState);
            work->sub_index = 0xC;
        } else if (state == 2) {
            work->sub_index = (work->sub_index + 1);
        }
    }
    Script_AnimStepLoop();
    Fishing_DrawDimScreen();
}
