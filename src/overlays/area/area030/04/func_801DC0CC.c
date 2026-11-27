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
    Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, g_Actors[g_FishingHookedFish].unk_06);

    offset = g_FishingHookedFish * 0x98;
    Fishing_DrawCatchRow(g_Actors[g_FishingHookedFish].unk_06, D_80146918[offset], 0);
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_CATCH_RANK_Y);
    Fishing_DrawIconRow(8, FISHING_CATCH_ROW_Y, 68);

    if ((g_PadStates[0].pressed & (PADLup | PADLdown)) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        work            = SELF(FishingState);
        work->cue_index = (work->cue_index ^ 0x1);
    } else if ((g_PadStates[0].pressed & PADRdown) != 0) {
        cue = 0x103;
        SND_SEPlay(cue);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        work            = SELF(FishingState);
        work->sub_index = (work->sub_index + 1);
    } else if ((g_PadStates[0].pressed & PADRup) != 0) {
        cue             = 0x106;
        work            = SELF(FishingState);
        work->cue_index = 1;
        SND_SEPlay(cue);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        work            = SELF(FishingState);
        work->sub_index = (work->sub_index + 1);
    }
    UI_CursorDraw(32, SELF(FishingState)->cue_index * 12 + 182, 0);
    Script_AnimStepLoop();
    Fishing_DrawDimScreen();
}
