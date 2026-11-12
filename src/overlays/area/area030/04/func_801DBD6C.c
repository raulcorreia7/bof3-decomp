#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Draws the AREA030 prompt rows for the current slot and, at the end
 * of the fade, retires or advances the sub-state selected by the work byte. */
MATCH void func_801DBD6C(void) {
    FishingState* work;
    s32           offset;
    u16           cue;
    u8            state;

    work                = FISHING_STATE;
    work->step_timer_09 = (work->step_timer_09 - 1);

    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, D_8014688E[g_FishingHookedFish * 0x98]);

    offset = g_FishingHookedFish * 0x98;
    func_801E1004(D_8014688E[offset], D_80146918[offset], 0);
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_CATCH_RANK_Y);

    work  = FISHING_STATE;
    state = work->saved_index_0B;
    if (state == 1) {
        cue = 0x43;
        Fishing_DrawIconRow(8, work->step_timer_09 * FISHING_CATCH_ROW_STEP + FISHING_CATCH_ROW_Y, cue);
    } else if (state == 2) {
        cue = 0x42;
        Fishing_DrawIconRow(8, work->step_timer_09 * FISHING_CATCH_ROW_STEP + FISHING_CATCH_ROW_Y, cue);
    }

    work = FISHING_STATE;
    if (work->step_timer_09 == 0) {
        state = work->saved_index_0B;
        if (state == 1) {
            work->cue_index_06 = 0;
            work               = FISHING_STATE;
            work->sub_index_03 = 0xC;
        } else if (state == 2) {
            work->sub_index_03 = (work->sub_index_03 + 1);
        }
    }
    Actor_StepAnimLoop();
    Fishing_DrawDimScreen();
}
