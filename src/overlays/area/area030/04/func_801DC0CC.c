#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callees. */

/* Draws the AREA030 prompt rows for the current slot, queues the cue
 * the pad pair selects, toggles the caret and advances the panel step, then
 * places the caret row and runs the shared per-frame tails. */
MATCH void func_801DC0CC(void) {
    FishingState* work;
    s32           offset;
    u16           cue;

    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, D_8014688E[g_FishingHookedFish * 0x98]);

    offset = g_FishingHookedFish * 0x98;
    Fishing_DrawCatchRow(D_8014688E[offset], D_80146918[offset], 0);
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_CATCH_RANK_Y);
    Fishing_DrawIconRow(8, FISHING_CATCH_ROW_Y, 68);

    if ((g_InputPressed & (PADLup | PADLdown)) != 0) {
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 0));
        work            = FISHING_STATE;
        work->cue_index = (work->cue_index ^ 0x1);
    } else if ((g_InputPressed & PADRdown) != 0) {
        cue = 0x103;
        SND_PlaySE(cue);
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 2));
        work            = FISHING_STATE;
        work->sub_index = (work->sub_index + 1);
    } else if ((g_InputPressed & PADRup) != 0) {
        cue             = 0x106;
        work            = FISHING_STATE;
        work->cue_index = 1;
        SND_PlaySE(cue);
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 2));
        work            = FISHING_STATE;
        work->sub_index = (work->sub_index + 1);
    }
    Menu_DrawCursorSprite(32, FISHING_STATE->cue_index * 12 + 182, 0);
    Actor_StepAnimLoop();
    Fishing_DrawDimScreen();
}
